/*
 * Bittern Cache.
 *
 * Copyright(c) 2013, 2014, 2015, Twitter, Inc., All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 */

/*! \file */

#include "bittern_cache.h"

void
sm_clean_pwrite_hit_copy_from_cache_start(struct bittern_cache *bc,
						struct work_item *wi,
						struct bio *bio)
{
	int ret;
	struct cache_block *cache_block;

	ASSERT((wi->wi_flags & WI_FLAG_BIO_CLONED) != 0);
	ASSERT((wi->wi_flags & WI_FLAG_HAS_ENDIO) == 0);
	ASSERT((wi->wi_flags & WI_FLAG_MAP_IO) != 0);
	ASSERT(wi->wi_io_endio == NULL);
	ASSERT(wi->wi_original_bio != NULL);
	cache_block = wi->wi_cache_block;

	ASSERT(bio != NULL);
	ASSERT(bio_is_request_single_cache_block(bio));
	ASSERT(cache_block->bcb_sector ==
	       bio_sector_to_cache_block_sector(bio));
	ASSERT(bio == wi->wi_original_bio);
	ASSERT(wi->wi_cache == bc);
	ASSERT(cache_block->bcb_state ==
	       CACHE_VALID_CLEAN_PARTIAL_WRITE_HIT_COPY_FROM_CACHE_START
	       || cache_block->bcb_state ==
	       CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_COPY_FROM_CACHE_START);
	ASSERT((wi->wi_flags & WI_FLAG_WRITE_CLONING) == 0);
	ASSERT(wi->wi_original_cache_block == NULL);

	if (cache_block->bcb_state ==
	    CACHE_VALID_CLEAN_PARTIAL_WRITE_HIT_COPY_FROM_CACHE_START) {
		cache_state_transition3(bc, cache_block,
						CACHE_TRANSITION_PATH_PARTIAL_WRITE_HIT_WT,
						CACHE_VALID_CLEAN_PARTIAL_WRITE_HIT_COPY_FROM_CACHE_START,
						CACHE_VALID_CLEAN_PARTIAL_WRITE_HIT_COPY_TO_DEVICE_STARTIO);
	} else {
		ASSERT(cache_block->bcb_state ==
		       CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_COPY_FROM_CACHE_START);
		cache_state_transition3(bc, cache_block,
						CACHE_TRANSITION_PATH_PARTIAL_WRITE_HIT_WB_CLEAN,
						CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_COPY_FROM_CACHE_START,
						CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_COPY_TO_CACHE_START);
	}

	BT_TRACE(BT_LEVEL_TRACE2, bc, wi, cache_block, bio, NULL,
		 "start_async_read (get_page_read): wi=%p, bc=%p, cache_block=%p, bio=%p",
		 wi, bc, cache_block, bio);
	ret = pmem_data_get_page_read(bc, cache_block->bcb_block_id, cache_block, &wi->wi_cache_data, &wi->wi_async_context, wi,	/*callback context */
							  cache_get_page_read_callback
							  /*callback function */
							  );
	M_ASSERT_FIXME(ret == 0);
}

void sm_dirty_write_miss_copy_to_cache_start(struct bittern_cache *bc,
						   struct work_item *wi,
						   struct bio *bio)
{
	int ret;
	uint128_t hash_data;
	struct cache_block *cache_block;

	ASSERT((wi->wi_flags & WI_FLAG_WRITE_CLONING) == 0);
	ASSERT(wi->wi_original_cache_block == NULL);
	ASSERT(wi->wi_cache == bc);
	cache_block = wi->wi_cache_block;
	BT_TRACE(BT_LEVEL_TRACE2, bc, wi, cache_block, bio, NULL,
		 "wi=%p, bc=%p, cache_block=%p, bio=%p", wi, bc, cache_block,
		 bio);

	ASSERT(bio != NULL);
	ASSERT(bio_is_request_single_cache_block(bio));
	ASSERT(cache_block->bcb_sector ==
	       bio_sector_to_cache_block_sector(bio));
	ASSERT(bio == wi->wi_original_bio);
	ASSERT(cache_block->bcb_state ==
	       CACHE_VALID_DIRTY_WRITE_MISS_COPY_TO_CACHE_START ||
	       cache_block->bcb_state ==
	       CACHE_VALID_DIRTY_WRITE_HIT_COPY_TO_CACHE_START ||
	       cache_block->bcb_state ==
	       CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_COPY_TO_CACHE_START);

	ASSERT(bio != NULL);
	ASSERT(bio_is_request_single_cache_block(bio));
	ASSERT(cache_block->bcb_sector ==
	       bio_sector_to_cache_block_sector(bio));
	ASSERT(bio == wi->wi_original_bio);

	ASSERT((wi->wi_flags & WI_FLAG_WRITE_CLONING) == 0);
	ASSERT(wi->wi_original_cache_block == NULL);

	if (cache_block->bcb_state ==
	    CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_COPY_TO_CACHE_START) {
		ASSERT(atomic_read(&wi->wi_cache_data.di_busy) == 1);
		ASSERT(wi->wi_cache_data.di_buffer != NULL);
		ASSERT(wi->wi_cache_data.di_page != NULL);

		ASSERT(bc->bc_enable_extra_checksum_check == 0
		       || bc->bc_enable_extra_checksum_check == 1);
		if (bc->bc_enable_extra_checksum_check != 0) {
			/* verify that hash is correct */
			cache_verify_hash_data_buffer(bc,
						cache_block,
						wi->wi_cache_data.di_buffer);
		}

		/* check hash */
		cache_track_hash_check(bc,
				       cache_block,
				       cache_block->bcb_hash_data);

		/*
		 * convert to write
		 */
		ASSERT(atomic_read(&wi->wi_cache_data.di_busy) == 1);
		ret = pmem_data_convert_read_to_write(bc,
						      cache_block->bcb_block_id,
						      cache_block,
						      &wi->wi_cache_data);
		M_ASSERT_FIXME(ret == 0);
	} else {
		ASSERT(cache_block->bcb_state ==
		       CACHE_VALID_DIRTY_WRITE_MISS_COPY_TO_CACHE_START ||
		       cache_block->bcb_state ==
		       CACHE_VALID_DIRTY_WRITE_HIT_COPY_TO_CACHE_START);
		/*
		 * get page for write
		 */
		ASSERT(atomic_read(&wi->wi_cache_data.di_busy) == 0);
		ret = pmem_data_get_page_write(bc,
					       cache_block->bcb_block_id,
								   cache_block,
					       &wi->wi_cache_data);
		M_ASSERT_FIXME(ret == 0);
	}
	ASSERT(wi->wi_cache_data.di_page != NULL);
	ASSERT(atomic_read(&wi->wi_cache_data.di_busy) == 1);

	/*
	 * copy to cache from bio, aka userland writes
	 */
	bio_copy_to_cache(wi, bio, &hash_data);

	/* update hash */
	cache_block->bcb_hash_data = hash_data;

	/*
	 * update hash
	 */
	cache_track_hash_set(bc, cache_block, cache_block->bcb_hash_data);

	if (cache_block->bcb_state ==
	    CACHE_VALID_DIRTY_WRITE_MISS_COPY_TO_CACHE_START) {
		cache_state_transition3(bc, cache_block,
						CACHE_TRANSITION_PATH_WRITE_MISS_WB,
						CACHE_VALID_DIRTY_WRITE_MISS_COPY_TO_CACHE_START,
						CACHE_VALID_DIRTY_WRITE_MISS_COPY_TO_CACHE_END);
	} else if (cache_block->bcb_state ==
		   CACHE_VALID_DIRTY_WRITE_HIT_COPY_TO_CACHE_START) {
		cache_state_transition3(bc, cache_block,
						CACHE_TRANSITION_PATH_WRITE_HIT_WB_CLEAN,
						CACHE_VALID_DIRTY_WRITE_HIT_COPY_TO_CACHE_START,
						CACHE_VALID_DIRTY_WRITE_HIT_COPY_TO_CACHE_END);
	} else {
		ASSERT(cache_block->bcb_state ==
		       CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_COPY_TO_CACHE_START);
		cache_state_transition3(bc, cache_block,
						CACHE_TRANSITION_PATH_PARTIAL_WRITE_HIT_WB_CLEAN,
						CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_COPY_TO_CACHE_START,
						CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_COPY_TO_CACHE_END);
	}

	/*
	 * release cache page
	 */
	ASSERT(atomic_read(&wi->wi_cache_data.di_busy) == 1);

	BT_TRACE(BT_LEVEL_TRACE2, bc, wi, cache_block, bio, NULL,
		 "start_async_write (put_page_write): callback_context/wi=%p, bc=%p, cache_block=%p, bio=%p",
		 wi, bc, cache_block, bio);
	ret = pmem_data_put_page_write(bc,
				       cache_block->bcb_block_id,
				       cache_block,
				       &wi->wi_cache_data,
				       &wi->wi_async_context,
				       wi,	/*callback context */
				       cache_put_page_write_callback,
							   CACHE_VALID_DIRTY);
	M_ASSERT_FIXME(ret == 0);

	ASSERT_BITTERN_CACHE(bc);
}

void sm_dirty_write_miss_copy_to_cache_end(struct bittern_cache *bc,
						 struct work_item *wi,
						 struct bio *bio)
{
	unsigned long cache_flags;
	struct cache_block *cache_block;
	enum cache_state original_state;

	ASSERT((wi->wi_flags & WI_FLAG_BIO_CLONED) != 0);
	ASSERT((wi->wi_flags & WI_FLAG_HAS_ENDIO) == 0);
	ASSERT((wi->wi_flags & WI_FLAG_MAP_IO) != 0);
	ASSERT(wi->wi_io_endio == NULL);
	ASSERT(wi->wi_original_bio != NULL);
	cache_block = wi->wi_cache_block;
	original_state = cache_block->bcb_state;
	BT_TRACE(BT_LEVEL_TRACE2, bc, wi, cache_block, bio, NULL,
		 "wi=%p, bc=%p, cache_block=%p, bio=%p", wi, bc, cache_block,
		 bio);

	ASSERT(bio != NULL);
	ASSERT(bio_is_request_single_cache_block(bio));
	ASSERT(cache_block->bcb_sector ==
	       bio_sector_to_cache_block_sector(bio));
	ASSERT(bio == wi->wi_original_bio);

	ASSERT(cache_block->bcb_state ==
	       CACHE_VALID_DIRTY_WRITE_MISS_COPY_TO_CACHE_END ||
	       cache_block->bcb_state ==
	       CACHE_VALID_DIRTY_WRITE_HIT_COPY_TO_CACHE_END ||
	       cache_block->bcb_state ==
	       CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_COPY_TO_CACHE_END);
	ASSERT((wi->wi_flags & WI_FLAG_WRITE_CLONING) == 0);
	ASSERT(wi->wi_original_cache_block == NULL);

	BT_TRACE(BT_LEVEL_TRACE2, bc, wi, cache_block, bio, NULL,
		 "write-{miss}-complete");

	ASSERT_CACHE_STATE(cache_block);
	ASSERT_BITTERN_CACHE(bc);
	ASSERT_WORK_ITEM(wi, bc);
	ASSERT_CACHE_BLOCK(cache_block, bc);

	ASSERT(cache_block->bcb_state ==
	       CACHE_VALID_DIRTY_WRITE_MISS_COPY_TO_CACHE_END ||
	       cache_block->bcb_state ==
	       CACHE_VALID_DIRTY_WRITE_HIT_COPY_TO_CACHE_END ||
	       cache_block->bcb_state ==
	       CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_COPY_TO_CACHE_END);
	spin_lock_irqsave(&cache_block->bcb_spinlock, cache_flags);
	cache_state_transition_final(bc,
					     cache_block,
					     CACHE_TRANSITION_PATH_NONE,
					     CACHE_VALID_DIRTY);
	spin_unlock_irqrestore(&cache_block->bcb_spinlock, cache_flags);
	cache_put_update_age(bc, cache_block, 1);

	ASSERT((wi->wi_flags & WI_FLAG_MAP_IO) != 0);
	ASSERT((wi->wi_flags & WI_FLAG_BIO_CLONED) != 0);

	if (original_state ==
	    CACHE_VALID_DIRTY_WRITE_MISS_COPY_TO_CACHE_END) {
		cache_timer_add(&bc->bc_timer_writes,
					wi->wi_ts_started);
		cache_timer_add(&bc->bc_timer_write_misses,
					wi->wi_ts_started);
		cache_timer_add(&bc->bc_timer_write_dirty_misses,
					wi->wi_ts_started);
	} else if (original_state ==
		   CACHE_VALID_DIRTY_WRITE_HIT_COPY_TO_CACHE_END) {
		cache_timer_add(&bc->bc_timer_writes,
					wi->wi_ts_started);
		cache_timer_add(&bc->bc_timer_write_hits,
					wi->wi_ts_started);
		cache_timer_add(&bc->bc_timer_write_dirty_hits,
					wi->wi_ts_started);
	} else {
		ASSERT(original_state ==
		       CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_COPY_TO_CACHE_END);
		cache_timer_add(&bc->bc_timer_writes,
					wi->wi_ts_started);
		cache_timer_add(&bc->bc_timer_write_hits,
					wi->wi_ts_started);
	}

	work_item_free(bc, wi);

	atomic_dec(&bc->bc_pending_requests);
	if (bio_data_dir(bio) == WRITE) {
		atomic_dec(&bc->bc_pending_write_requests);
		atomic_inc(&bc->bc_completed_write_requests);
	} else {
		atomic_dec(&bc->bc_pending_read_requests);
		atomic_inc(&bc->bc_completed_read_requests);
	}
	atomic_inc(&bc->bc_completed_requests);
	/*
	 * wakeup possible waiters
	 */
	cache_wakeup_deferred(bc);
	bio_endio(bio, 0);
}

void sm_clean_write_miss_copy_to_device_startio(struct bittern_cache *bc,
						      struct work_item *wi,
						      struct bio *bio)
{
	struct bio *cloned_bio;
	int ret;
	uint128_t hash_data;
	struct cache_block *cache_block;
	int val;

	ASSERT((wi->wi_flags & WI_FLAG_BIO_CLONED) != 0);
	ASSERT((wi->wi_flags & WI_FLAG_HAS_ENDIO) == 0);
	ASSERT((wi->wi_flags & WI_FLAG_MAP_IO) != 0);
	ASSERT(wi->wi_io_endio == NULL);
	ASSERT(wi->wi_original_bio != NULL);
	cache_block = wi->wi_cache_block;

	ASSERT(bio != NULL);
	ASSERT(bio_is_request_single_cache_block(bio));
	ASSERT(cache_block->bcb_sector ==
	       bio_sector_to_cache_block_sector(bio));
	ASSERT(bio == wi->wi_original_bio);
	ASSERT(cache_block->bcb_state ==
	       CACHE_VALID_CLEAN_WRITE_MISS_COPY_TO_DEVICE_STARTIO
	       || cache_block->bcb_state ==
	       CACHE_VALID_CLEAN_WRITE_HIT_COPY_TO_DEVICE_STARTIO
	       || cache_block->bcb_state ==
	       CACHE_VALID_CLEAN_PARTIAL_WRITE_HIT_COPY_TO_DEVICE_STARTIO);
	ASSERT((wi->wi_flags & WI_FLAG_WRITE_CLONING) == 0);
	ASSERT(wi->wi_original_cache_block == NULL);

	if (cache_block->bcb_state ==
	    CACHE_VALID_CLEAN_PARTIAL_WRITE_HIT_COPY_TO_DEVICE_STARTIO)
	{
		/*
		 * convert to write
		 */
		ASSERT(atomic_read(&wi->wi_cache_data.di_busy) == 1);
		ret = pmem_data_convert_read_to_write(bc,
						      cache_block->bcb_block_id,
						      cache_block,
						      &wi->wi_cache_data);
		M_ASSERT_FIXME(ret == 0);
	} else {
		ASSERT(cache_block->bcb_state ==
		       CACHE_VALID_CLEAN_WRITE_MISS_COPY_TO_DEVICE_STARTIO
		       || cache_block->bcb_state ==
		       CACHE_VALID_CLEAN_WRITE_HIT_COPY_TO_DEVICE_STARTIO);
		/*
		 * get page for write
		 */
		ASSERT(atomic_read(&wi->wi_cache_data.di_busy) == 0);
		ret = pmem_data_get_page_write(bc,
					       cache_block->bcb_block_id,
								   cache_block,
					       &wi->wi_cache_data);
		M_ASSERT_FIXME(ret == 0);
	}
	ASSERT(wi->wi_cache_data.di_page != NULL);
	ASSERT(atomic_read(&wi->wi_cache_data.di_busy) == 1);

	BT_TRACE(BT_LEVEL_TRACE2, bc, wi, cache_block, bio, NULL,
		 "di_buffer=%p, di_page=%p", wi->wi_cache_data.di_buffer,
		 wi->wi_cache_data.di_page);

	/*
	 * copy to cache from bio, aka userland writes
	 */
	bio_copy_to_cache(wi, bio, &hash_data);

	/* update hash */
	cache_block->bcb_hash_data = hash_data;

	/*
	 * update hash
	 */
	cache_track_hash_set(bc, cache_block, cache_block->bcb_hash_data);

	/*
	 * set up a new bio for write
	 */
	cloned_bio = bio_alloc(GFP_ATOMIC, 1);
	M_ASSERT_FIXME(cloned_bio != NULL);

	ASSERT(wi->wi_original_bio == bio);
	ASSERT(wi->wi_cloned_bio == NULL);
	wi->wi_cloned_bio = cloned_bio;
	ASSERT(wi->wi_cache == bc);
	ASSERT(wi->wi_cache_block == cache_block);

	/*
	 * Here we always write the full page.
	 * For partial writes, we previously read-in the whole page,
	 * then modified a part of it with data from userland.
	 */

	/*
	 * we are writing from cache into the device
	 */
	bio_set_data_dir_write(cloned_bio);
	ASSERT(bio_data_dir(cloned_bio) == WRITE);

	cloned_bio->bi_iter.bi_sector = bio_sector_to_cache_block_sector(bio);
	cloned_bio->bi_iter.bi_size = PAGE_SIZE;
	cloned_bio->bi_bdev = bc->bc_dev->bdev;
	cloned_bio->bi_end_io = cache_state_machine_endio;
	cloned_bio->bi_private = wi;
	cloned_bio->bi_io_vec[0].bv_page = wi->wi_cache_data.di_page;
	cloned_bio->bi_io_vec[0].bv_len = PAGE_SIZE;
	cloned_bio->bi_io_vec[0].bv_offset = 0;
	cloned_bio->bi_vcnt = 1;

	if (bio->bi_iter.bi_size == PAGE_SIZE) {
		ASSERT(bio->bi_iter.bi_sector == cloned_bio->bi_iter.bi_sector);
		ASSERT(bio->bi_iter.bi_size == cloned_bio->bi_iter.bi_size);
	}

	BT_TRACE(BT_LEVEL_TRACE2, bc, wi, cache_block, bio, wi->wi_cloned_bio,
		 "copy-to-device");

	atomic_inc(&bc->bc_write_cached_device_requests);
	val = atomic_inc_return(&bc->bc_pending_cached_device_requests);
	atomic_set_if_higher(&bc->bc_highest_pending_cached_device_requests,
			     val);

	BT_TRACE(BT_LEVEL_TRACE2, bc, wi, cache_block, bio, wi->wi_cloned_bio,
		 "copy-to-device-starting-io");

	ASSERT_BITTERN_CACHE(bc);
	ASSERT_CACHE_BLOCK(cache_block, bc);
	ASSERT_WORK_ITEM(wi, bc);

	if (cache_block->bcb_state ==
	    CACHE_VALID_CLEAN_WRITE_MISS_COPY_TO_DEVICE_STARTIO) {
		cache_state_transition3(bc, cache_block,
						CACHE_TRANSITION_PATH_WRITE_MISS_WT,
						CACHE_VALID_CLEAN_WRITE_MISS_COPY_TO_DEVICE_STARTIO,
						CACHE_VALID_CLEAN_WRITE_MISS_COPY_TO_DEVICE_ENDIO);
		/*
		 * first step in state machine -- in a process context
		 */
		wi->wi_ts_physio = current_kernel_time_nsec();
		generic_make_request(cloned_bio);
	} else if (cache_block->bcb_state ==
		   CACHE_VALID_CLEAN_WRITE_HIT_COPY_TO_DEVICE_STARTIO) {
		cache_state_transition3(bc, cache_block,
						CACHE_TRANSITION_PATH_WRITE_HIT_WT,
						CACHE_VALID_CLEAN_WRITE_HIT_COPY_TO_DEVICE_STARTIO,
						CACHE_VALID_CLEAN_WRITE_HIT_COPY_TO_DEVICE_ENDIO);
		/*
		 * first step in state machine -- in a process context
		 */
		wi->wi_ts_physio = current_kernel_time_nsec();
		generic_make_request(cloned_bio);
	} else {
		ASSERT(cache_block->bcb_state ==
		       CACHE_VALID_CLEAN_PARTIAL_WRITE_HIT_COPY_TO_DEVICE_STARTIO);
		cache_state_transition3(bc, cache_block,
						CACHE_TRANSITION_PATH_PARTIAL_WRITE_HIT_WT,
						CACHE_VALID_CLEAN_PARTIAL_WRITE_HIT_COPY_TO_DEVICE_STARTIO,
						CACHE_VALID_CLEAN_PARTIAL_WRITE_HIT_COPY_TO_DEVICE_ENDIO);
		/*
		 * we are potentially in interrupt context
		 */
		/*
		 * FIXME: add API to tell us if asyncread is sync or async and
		 * decide based on it
		 */
		wi->wi_ts_workqueue = current_kernel_time_nsec();
		INIT_WORK(&wi->wi_work, cache_make_request_worker);
		ret = queue_work(bc->bc_make_request_wq, &wi->wi_work);
		BT_TRACE(BT_LEVEL_TRACE1, bc, wi, cache_block, bio,
			 wi->wi_cloned_bio, "queue_work=%d", ret);
		ASSERT(ret == 1);
	}
}

void sm_clean_write_miss_copy_to_device_endio(struct bittern_cache *bc,
						    struct work_item *wi,
						    struct bio *bio)
{
	int ret;
	enum cache_state original_state;
	struct cache_block *cache_block;

	ASSERT((wi->wi_flags & WI_FLAG_BIO_CLONED) != 0);
	ASSERT((wi->wi_flags & WI_FLAG_HAS_ENDIO) == 0);
	ASSERT((wi->wi_flags & WI_FLAG_MAP_IO) != 0);
	ASSERT(wi->wi_io_endio == NULL);
	ASSERT(wi->wi_original_bio != NULL);
	cache_block = wi->wi_cache_block;
	original_state = cache_block->bcb_state;

	ASSERT(bio != NULL);
	ASSERT(bio_is_request_single_cache_block(bio));
	ASSERT(cache_block->bcb_sector ==
	       bio_sector_to_cache_block_sector(bio));
	ASSERT(bio == wi->wi_original_bio);
	ASSERT(cache_block->bcb_state ==
	       CACHE_VALID_CLEAN_WRITE_MISS_COPY_TO_DEVICE_ENDIO
	       || cache_block->bcb_state ==
	       CACHE_VALID_CLEAN_WRITE_HIT_COPY_TO_DEVICE_ENDIO
	       || cache_block->bcb_state ==
	       CACHE_VALID_CLEAN_PARTIAL_WRITE_HIT_COPY_TO_DEVICE_ENDIO);
	ASSERT((wi->wi_flags & WI_FLAG_WRITE_CLONING) == 0);
	ASSERT(wi->wi_original_cache_block == NULL);

	BT_TRACE(BT_LEVEL_TRACE1, bc, wi, cache_block, bio, NULL,
		 "copy-to-device-io-done");
	ASSERT((wi->wi_flags & WI_FLAG_WRITE_CLONING) == 0);
	ASSERT(wi->wi_original_cache_block == NULL);

	ASSERT_CACHE_STATE(cache_block);
	ASSERT((wi->wi_flags & WI_FLAG_MAP_IO) != 0);
	ASSERT((wi->wi_flags & WI_FLAG_BIO_CLONED) != 0);
	atomic_dec(&bc->bc_pending_cached_device_requests);
	ASSERT_CACHE_BLOCK(cache_block, bc);

	if (cache_block->bcb_state ==
	    CACHE_VALID_CLEAN_WRITE_MISS_COPY_TO_DEVICE_ENDIO) {
		cache_state_transition3(bc, cache_block,
						CACHE_TRANSITION_PATH_WRITE_MISS_WT,
						CACHE_VALID_CLEAN_WRITE_MISS_COPY_TO_DEVICE_ENDIO,
						CACHE_VALID_CLEAN_WRITE_MISS_COPY_TO_CACHE_END);
	} else if (cache_block->bcb_state ==
		   CACHE_VALID_CLEAN_WRITE_HIT_COPY_TO_DEVICE_ENDIO) {
		cache_state_transition3(bc, cache_block,
						CACHE_TRANSITION_PATH_WRITE_HIT_WT,
						CACHE_VALID_CLEAN_WRITE_HIT_COPY_TO_DEVICE_ENDIO,
						CACHE_VALID_CLEAN_WRITE_HIT_COPY_TO_CACHE_END);
	} else {
		ASSERT(cache_block->bcb_state ==
		       CACHE_VALID_CLEAN_PARTIAL_WRITE_HIT_COPY_TO_DEVICE_ENDIO);
		cache_state_transition3(bc, cache_block,
						CACHE_TRANSITION_PATH_PARTIAL_WRITE_HIT_WT,
						CACHE_VALID_CLEAN_PARTIAL_WRITE_HIT_COPY_TO_DEVICE_ENDIO,
						CACHE_VALID_CLEAN_PARTIAL_WRITE_HIT_COPY_TO_CACHE_END);
	}

	/*
	 * release cache page
	 */
	ASSERT(atomic_read(&wi->wi_cache_data.di_busy) == 1);

	BT_TRACE(BT_LEVEL_TRACE2, bc, wi, cache_block, bio, NULL,
		 "start_async_write (put_page_write): callback_context/wi=%p, bc=%p, cache_block=%p, bio=%p",
		 wi, bc, cache_block, bio);
	ret = pmem_data_put_page_write(bc,
				       cache_block->bcb_block_id,
				       cache_block,
				       &wi->wi_cache_data,
				       &wi->wi_async_context,
				       wi,	/*callback context */
				       cache_put_page_write_callback,
							   CACHE_VALID_CLEAN);

	M_ASSERT_FIXME(ret == 0);

	ASSERT_BITTERN_CACHE(bc);
}

void sm_clean_write_miss_copy_to_cache_end(struct bittern_cache *bc,
						 struct work_item *wi,
						 struct bio *bio)
{
	unsigned long cache_flags;
	enum cache_state original_state;
	struct cache_block *cache_block;

	ASSERT((wi->wi_flags & WI_FLAG_BIO_CLONED) != 0);
	ASSERT((wi->wi_flags & WI_FLAG_HAS_ENDIO) == 0);
	ASSERT((wi->wi_flags & WI_FLAG_MAP_IO) != 0);
	ASSERT(wi->wi_io_endio == NULL);
	ASSERT(wi->wi_original_bio != NULL);
	cache_block = wi->wi_cache_block;
	original_state = cache_block->bcb_state;

	ASSERT(bio != NULL);
	ASSERT(bio_is_request_single_cache_block(bio));
	ASSERT(cache_block->bcb_sector ==
	       bio_sector_to_cache_block_sector(bio));
	ASSERT(bio == wi->wi_original_bio);
	ASSERT(cache_block->bcb_state ==
	       CACHE_VALID_CLEAN_WRITE_MISS_COPY_TO_CACHE_END
	       || cache_block->bcb_state ==
	       CACHE_VALID_CLEAN_WRITE_HIT_COPY_TO_CACHE_END
	       || cache_block->bcb_state ==
	       CACHE_VALID_CLEAN_PARTIAL_WRITE_HIT_COPY_TO_CACHE_END);
	ASSERT((wi->wi_flags & WI_FLAG_WRITE_CLONING) == 0);
	ASSERT(wi->wi_original_cache_block == NULL);

	BT_TRACE(BT_LEVEL_TRACE1, bc, wi, cache_block, bio, NULL,
		 "copy-to-cache-end");

	spin_lock_irqsave(&cache_block->bcb_spinlock, cache_flags);
	cache_state_transition_final(bc,
					     cache_block,
					     CACHE_TRANSITION_PATH_NONE,
					     CACHE_VALID_CLEAN);
	spin_unlock_irqrestore(&cache_block->bcb_spinlock, cache_flags);
	cache_put_update_age(bc, cache_block, 1);

	cache_timer_add(&bc->bc_timer_writes, wi->wi_ts_started);
	if (original_state ==
	    CACHE_VALID_CLEAN_WRITE_MISS_COPY_TO_CACHE_END) {
		cache_timer_add(&bc->bc_timer_write_misses,
					wi->wi_ts_started);
		cache_timer_add(&bc->bc_timer_write_clean_misses,
					wi->wi_ts_started);
	} else {
		ASSERT(original_state ==
		       CACHE_VALID_CLEAN_WRITE_HIT_COPY_TO_CACHE_END
		       || original_state ==
		       CACHE_VALID_CLEAN_PARTIAL_WRITE_HIT_COPY_TO_CACHE_END);
		cache_timer_add(&bc->bc_timer_write_hits,
					wi->wi_ts_started);
		cache_timer_add(&bc->bc_timer_write_clean_hits,
					wi->wi_ts_started);
	}

	work_item_free(bc, wi);

	atomic_dec(&bc->bc_pending_requests);
	if (bio_data_dir(bio) == WRITE) {
		atomic_dec(&bc->bc_pending_write_requests);
		atomic_inc(&bc->bc_completed_write_requests);
	} else {
		atomic_dec(&bc->bc_pending_read_requests);
		atomic_inc(&bc->bc_completed_read_requests);
	}
	atomic_inc(&bc->bc_completed_requests);
	/*
	 * wakeup possible waiters
	 */
	cache_wakeup_deferred(bc);
	bio_endio(bio, 0);
}

void
sm_dirty_pwrite_hit_clone_copy_from_cache_start(struct bittern_cache *bc,
						      struct work_item *wi,
						      struct bio *bio)
{
	int ret;
	struct cache_block *cache_block;
	struct cache_block *original_cache_block;

	ASSERT(wi->wi_original_cache_block != NULL);
	ASSERT((wi->wi_flags & WI_FLAG_BIO_CLONED) != 0);
	ASSERT((wi->wi_flags & WI_FLAG_HAS_ENDIO) == 0);
	ASSERT((wi->wi_flags & WI_FLAG_MAP_IO) != 0);
	ASSERT(wi->wi_io_endio == NULL);
	ASSERT(wi->wi_original_bio != NULL);
	cache_block = wi->wi_cache_block;
	original_cache_block = wi->wi_original_cache_block;

	ASSERT(bio != NULL);
	ASSERT(bio_is_request_single_cache_block(bio));
	ASSERT(cache_block->bcb_sector ==
	       bio_sector_to_cache_block_sector(bio));
	ASSERT(bio == wi->wi_original_bio);
	ASSERT(wi->wi_cache == bc);
	ASSERT(cache_block->bcb_state ==
	       CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_DWC_COPY_FROM_ORIGINAL_CACHE_START);

	ASSERT((wi->wi_flags & WI_FLAG_WRITE_CLONING) != 0);
	ASSERT_CACHE_BLOCK(cache_block, bc);
	ASSERT(cache_block == wi->wi_cache_block);
	ASSERT(original_cache_block == wi->wi_original_cache_block);
	ASSERT_CACHE_BLOCK(original_cache_block, bc);
	ASSERT(original_cache_block->bcb_state ==
	       CACHE_VALID_DIRTY_INVALIDATE_START);
	ASSERT(original_cache_block->bcb_sector == cache_block->bcb_sector);

	cache_state_transition3(bc,
					cache_block,
					CACHE_TRANSITION_PATH_PARTIAL_WRITE_HIT_WB_DIRTY_DWC_CLONE,
					CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_DWC_COPY_FROM_ORIGINAL_CACHE_START,
					CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_DWC_COPY_TO_CLONED_CACHE_START);

	BT_TRACE(BT_LEVEL_TRACE2, bc, wi, cache_block, bio, NULL,
		 "wi=%p, bc=%p, cache_block=%p, bio=%p", wi, bc, cache_block,
		 bio);
	BT_TRACE(BT_LEVEL_TRACE2, bc, wi, original_cache_block, bio, NULL,
		 "start_async_read (get_page_read): wi=%p, bc=%p, original_cache_block=%p, bio=%p",
		 wi, bc, original_cache_block, bio);
	ret = pmem_data_get_page_read(bc, original_cache_block->bcb_block_id, original_cache_block, &wi->wi_cache_data, &wi->wi_async_context, wi,	/*callback context */
							  cache_get_page_read_callback
							  /*callback function */
							  );
	M_ASSERT_FIXME(ret == 0);
}

void
sm_dirty_write_hit_clone_copy_to_cache_start(struct bittern_cache *bc,
						   struct work_item *wi,
						   struct bio *bio)
{
	int ret;
	uint128_t hash_data;
	struct cache_block *cache_block;
	struct cache_block *original_cache_block;
	ASSERT(wi->wi_original_cache_block != NULL);

	/*
	 * for dirty write hit case, cache_block here is cloned cache block
	 */
	ASSERT((wi->wi_flags & WI_FLAG_BIO_CLONED) != 0);
	ASSERT((wi->wi_flags & WI_FLAG_HAS_ENDIO) == 0);
	ASSERT((wi->wi_flags & WI_FLAG_MAP_IO) != 0);
	ASSERT(wi->wi_io_endio == NULL);
	ASSERT(wi->wi_original_bio != NULL);
	cache_block = wi->wi_cache_block;
	original_cache_block = wi->wi_original_cache_block;

	ASSERT(bio != NULL);
	ASSERT(bio_is_request_single_cache_block(bio));
	ASSERT(cache_block->bcb_sector ==
	       bio_sector_to_cache_block_sector(bio));
	ASSERT(bio == wi->wi_original_bio);
	ASSERT(wi->wi_original_cache_block != NULL);

	ASSERT(cache_block->bcb_state ==
	       CACHE_VALID_DIRTY_WRITE_HIT_DWC_COPY_TO_CACHE_START ||
	       cache_block->bcb_state ==
	       CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_DWC_COPY_TO_CLONED_CACHE_START);

	ASSERT((wi->wi_flags & WI_FLAG_WRITE_CLONING) != 0);
	ASSERT_CACHE_BLOCK(cache_block, bc);
	ASSERT(cache_block == wi->wi_cache_block);
	ASSERT(original_cache_block == wi->wi_original_cache_block);
	ASSERT_CACHE_BLOCK(original_cache_block, bc);
	ASSERT(original_cache_block->bcb_state ==
	       CACHE_VALID_DIRTY_INVALIDATE_START);
	ASSERT(original_cache_block->bcb_sector == cache_block->bcb_sector);

	if (cache_block->bcb_state ==
	    CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_DWC_COPY_TO_CLONED_CACHE_START)
	{
		ASSERT(atomic_read(&wi->wi_cache_data.di_busy) == 1);
		ASSERT(wi->wi_cache_data.di_buffer != NULL);
		ASSERT(wi->wi_cache_data.di_page != NULL);

		ASSERT(bc->bc_enable_extra_checksum_check == 0
		       || bc->bc_enable_extra_checksum_check == 1);
		if (bc->bc_enable_extra_checksum_check != 0) {
			/* verify that hash is correct */
			cache_verify_hash_data_buffer(bc,
						original_cache_block,
						wi->wi_cache_data.di_buffer);
		}

		/* check hash */
		cache_track_hash_check(bc,
					 original_cache_block,
					 original_cache_block->bcb_hash_data);

		/*
		 * clone read page to write page
		 */
		ASSERT(atomic_read(&wi->wi_cache_data.di_busy) == 1);
		ret = pmem_data_clone_read_to_write(bc,
					original_cache_block->bcb_block_id,
					original_cache_block,
					cache_block->bcb_block_id,
					cache_block,
					&wi->wi_cache_data);
		M_ASSERT_FIXME(ret == 0);
	} else {
		ASSERT(cache_block->bcb_state ==
		       CACHE_VALID_DIRTY_WRITE_HIT_DWC_COPY_TO_CACHE_START);
		/*
		 * get page for write
		 */
		ret = pmem_data_get_page_write(bc,
					       cache_block->bcb_block_id,
					       cache_block,
					       &wi->wi_cache_data);
		M_ASSERT_FIXME(ret == 0);
		ASSERT(wi->wi_cache_data.di_page != NULL);
		ASSERT(atomic_read(&wi->wi_cache_data.di_busy) == 1);
	}

	/*
	 * copy to cache from bio, aka userland writes
	 */
	bio_copy_to_cache(wi, bio, &hash_data);

	/* update hash */
	cache_block->bcb_hash_data = hash_data;

	/*
	 * update hash
	 */
	cache_track_hash_set(bc, cache_block,
				       cache_block->bcb_hash_data);

	if (cache_block->bcb_state ==
	    CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_DWC_COPY_TO_CLONED_CACHE_START)
	{
		cache_state_transition3(bc, cache_block,
						CACHE_TRANSITION_PATH_PARTIAL_WRITE_HIT_WB_DIRTY_DWC_CLONE,
						CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_DWC_COPY_TO_CLONED_CACHE_START,
						CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_DWC_COPY_TO_CLONED_CACHE_END);
	} else {
		ASSERT(cache_block->bcb_state ==
		       CACHE_VALID_DIRTY_WRITE_HIT_DWC_COPY_TO_CACHE_START);
		cache_state_transition3(bc, cache_block,
						CACHE_TRANSITION_PATH_WRITE_HIT_WB_DIRTY_DWC_CLONE,
						CACHE_VALID_DIRTY_WRITE_HIT_DWC_COPY_TO_CACHE_START,
						CACHE_VALID_DIRTY_WRITE_HIT_DWC_COPY_TO_CACHE_END);
	}

	/*
	 * release page
	 */
	BT_TRACE(BT_LEVEL_TRACE2, bc, wi, cache_block, bio, NULL,
		 "start_async_write (put_page_write): callback_context/wi=%p, bc=%p, cache_block=%p, bio=%p",
		 wi, bc, cache_block, bio);
	ret = pmem_data_put_page_write(bc, cache_block->bcb_block_id, cache_block, &wi->wi_cache_data, &wi->wi_async_context, wi,	/*callback context */
							   cache_put_page_write_callback,	/*callback function */
							   CACHE_VALID_DIRTY);

	M_ASSERT_FIXME(ret == 0);

	ASSERT_BITTERN_CACHE(bc);
}

void sm_dirty_write_hit_clone_copy_to_cache_end(struct bittern_cache *bc,
						      struct work_item *wi,
						      struct bio *bio)
{
	unsigned long cache_flags;
	struct cache_block *cache_block;
	struct cache_block *original_cache_block;
	int val;

	/*
	 * for dirty write hit case, cache_block here is cloned cache block
	 */

	ASSERT((wi->wi_flags & WI_FLAG_BIO_CLONED) != 0);
	ASSERT((wi->wi_flags & WI_FLAG_HAS_ENDIO) == 0);
	ASSERT((wi->wi_flags & WI_FLAG_MAP_IO) != 0);
	ASSERT(wi->wi_io_endio == NULL);
	ASSERT(wi->wi_original_bio != NULL);
	ASSERT(wi->wi_original_cache_block != NULL);
	cache_block = wi->wi_cache_block;
	original_cache_block = wi->wi_original_cache_block;
	BT_TRACE(BT_LEVEL_TRACE2, bc, wi, cache_block, bio, NULL,
		 "copy_to_cache_end");

	ASSERT(bio != NULL);
	ASSERT(bio_is_request_single_cache_block(bio));
	ASSERT(cache_block->bcb_sector ==
	       bio_sector_to_cache_block_sector(bio));
	ASSERT(bio == wi->wi_original_bio);
	ASSERT(cache_block->bcb_state ==
	       CACHE_VALID_DIRTY_WRITE_HIT_DWC_COPY_TO_CACHE_END
	       || cache_block->bcb_state ==
	       CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_DWC_COPY_TO_CLONED_CACHE_END);

	ASSERT((wi->wi_flags & WI_FLAG_WRITE_CLONING) != 0);
	ASSERT(wi->wi_original_cache_block != NULL);
	ASSERT_CACHE_BLOCK(cache_block, bc);
	ASSERT(cache_block == wi->wi_cache_block);
	ASSERT(original_cache_block == wi->wi_original_cache_block);
	ASSERT_CACHE_BLOCK(original_cache_block, bc);
	ASSERT(original_cache_block->bcb_state ==
	       CACHE_VALID_DIRTY_INVALIDATE_START);
	ASSERT(original_cache_block->bcb_sector == cache_block->bcb_sector);

	BT_TRACE(BT_LEVEL_TRACE2, bc, wi, cache_block, bio, NULL,
		 "copy_to_cache_end-1");
	/*
	 * STEP #1 -- complete new cache_block write request
	 */
	spin_lock_irqsave(&cache_block->bcb_spinlock, cache_flags);
	cache_state_transition_final(bc,
					     cache_block,
					     CACHE_TRANSITION_PATH_NONE,
					     CACHE_VALID_DIRTY);
	spin_unlock_irqrestore(&cache_block->bcb_spinlock, cache_flags);
	cache_put_update_age(bc, cache_block, 1);

	cache_timer_add(&bc->bc_timer_writes, wi->wi_ts_started);
	cache_timer_add(&bc->bc_timer_write_hits, wi->wi_ts_started);
	cache_timer_add(&bc->bc_timer_write_dirty_hits,
				wi->wi_ts_started);

	atomic_dec(&bc->bc_pending_requests);
	if (bio_data_dir(bio) == WRITE) {
		atomic_dec(&bc->bc_pending_write_requests);
		atomic_inc(&bc->bc_completed_write_requests);
	} else {
		atomic_dec(&bc->bc_pending_read_requests);
		atomic_inc(&bc->bc_completed_read_requests);
	}
	atomic_inc(&bc->bc_completed_requests);

	work_item_del_pending_io(bc, wi);

	bio_endio(bio, 0);

	/*
	 * wakeup possible waiters
	 */
	cache_wakeup_deferred(bc);

	/*
	 * STEP #2 -- now start an async metadata invalidation
	 */

	BT_TRACE(BT_LEVEL_TRACE2, bc, wi, original_cache_block, NULL, NULL,
		 "copy_to_cache_end-2");

	ASSERT(original_cache_block->bcb_transition_path ==
	       CACHE_TRANSITION_PATH_DIRTY_INVALIDATION_WB);
	ASSERT(original_cache_block->bcb_state ==
	       CACHE_VALID_DIRTY_INVALIDATE_START);

	work_item_reallocate(bc,
			     original_cache_block,
			     wi,
			     NULL,
			     (WI_FLAG_MAP_IO |
			      WI_FLAG_BIO_NOT_CLONED |
			      WI_FLAG_XID_USE_CACHE_BLOCK |
			      WI_FLAG_HAS_ENDIO),
			     cache_invalidate_block_io_end);

	wi->wi_ts_started = current_kernel_time_nsec();

	atomic_inc(&bc->bc_invalidations_map);
	val = atomic_inc_return(&bc->bc_pending_invalidate_requests);
	atomic_set_if_higher(&bc->bc_highest_pending_invalidate_requests, val);

	/*
	 * kick off state machine to write this out.
	 * cache_bgwriter_io_endio() will be called on completion.
	 */
	work_item_add_pending_io(bc,
				 wi,
				 'L',
				 original_cache_block->bcb_sector,
				 WRITE);
	ASSERT(wi->wi_cache_block == original_cache_block);
	cache_state_machine(bc, wi, NULL);
}
