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

const char *cache_state_to_str(enum cache_state cache_state)
{
	switch (cache_state) {
	case CACHE_INVALID:
		return "CACHE_INVALID";
	case CACHE_VALID_CLEAN:
		return "CACHE_VALID_CLEAN";
	case CACHE_VALID_CLEAN_NO_DATA:
		return "CACHE_VALID_CLEAN_NO_DATA";
	case CACHE_VALID_CLEAN_READ_MISS_COPY_FROM_DEVICE_STARTIO:
		return "CACHE_VALID_CLEAN_READ_MISS_COPY_FROM_DEVICE_STARTIO";
	case CACHE_VALID_CLEAN_READ_MISS_COPY_FROM_DEVICE_ENDIO:
		return "CACHE_VALID_CLEAN_READ_MISS_COPY_FROM_DEVICE_ENDIO";
	case CACHE_VALID_CLEAN_READ_MISS_COPY_TO_CACHE_END:
		return "CACHE_VALID_CLEAN_READ_MISS_COPY_TO_CACHE_END";
	case CACHE_VALID_CLEAN_READ_HIT_COPY_FROM_CACHE_START:
		return "CACHE_VALID_CLEAN_READ_HIT_COPY_FROM_CACHE_START";
	case CACHE_VALID_CLEAN_READ_HIT_COPY_FROM_CACHE_END:
		return "CACHE_VALID_CLEAN_READ_HIT_COPY_FROM_CACHE_END";
	case CACHE_VALID_CLEAN_WRITE_MISS_COPY_TO_DEVICE_STARTIO:
		return "CACHE_VALID_CLEAN_WRITE_MISS_COPY_TO_DEVICE_STARTIO";
	case CACHE_VALID_CLEAN_WRITE_MISS_COPY_TO_DEVICE_ENDIO:
		return "CACHE_VALID_CLEAN_WRITE_MISS_COPY_TO_DEVICE_ENDIO";
	case CACHE_VALID_CLEAN_WRITE_MISS_COPY_TO_CACHE_END:
		return "CACHE_VALID_CLEAN_WRITE_MISS_COPY_TO_CACHE_END";
	case CACHE_VALID_CLEAN_WRITE_HIT_COPY_TO_DEVICE_STARTIO:
		return "CACHE_VALID_CLEAN_WRITE_HIT_COPY_TO_DEVICE_STARTIO";
	case CACHE_VALID_CLEAN_WRITE_HIT_COPY_TO_DEVICE_ENDIO:
		return "CACHE_VALID_CLEAN_WRITE_HIT_COPY_TO_DEVICE_ENDIO";
	case CACHE_VALID_CLEAN_WRITE_HIT_COPY_TO_CACHE_END:
		return "CACHE_VALID_CLEAN_WRITE_HIT_COPY_TO_CACHE_END";
	case CACHE_VALID_CLEAN_PARTIAL_WRITE_HIT_COPY_FROM_CACHE_START:
		return
		    "CACHE_VALID_CLEAN_PARTIAL_WRITE_HIT_COPY_FROM_CACHE_START";
	case CACHE_VALID_CLEAN_PARTIAL_WRITE_HIT_COPY_TO_DEVICE_STARTIO:
		return
		    "CACHE_VALID_CLEAN_PARTIAL_WRITE_HIT_COPY_TO_DEVICE_STARTIO";
	case CACHE_VALID_CLEAN_PARTIAL_WRITE_HIT_COPY_TO_DEVICE_ENDIO:
		return
		    "CACHE_VALID_CLEAN_PARTIAL_WRITE_HIT_COPY_TO_DEVICE_ENDIO";
	case CACHE_VALID_CLEAN_PARTIAL_WRITE_HIT_COPY_TO_CACHE_END:
		return "CACHE_VALID_CLEAN_PARTIAL_WRITE_HIT_COPY_TO_CACHE_END";
	case CACHE_VALID_CLEAN_PARTIAL_WRITE_MISS_COPY_FROM_DEVICE_STARTIO:
		return
		    "CACHE_VALID_CLEAN_PARTIAL_WRITE_MISS_COPY_FROM_DEVICE_STARTIO";
	case CACHE_VALID_CLEAN_PARTIAL_WRITE_MISS_COPY_FROM_DEVICE_ENDIO:
		return
		    "CACHE_VALID_CLEAN_PARTIAL_WRITE_MISS_COPY_FROM_DEVICE_ENDIO";
	case CACHE_VALID_CLEAN_PARTIAL_WRITE_MISS_COPY_TO_CACHE_END:
		return "CACHE_VALID_CLEAN_PARTIAL_WRITE_MISS_COPY_TO_CACHE_END";
	case CACHE_VALID_CLEAN_PARTIAL_WRITE_MISS_COPY_TO_DEVICE_ENDIO:
		return
		    "CACHE_VALID_CLEAN_PARTIAL_WRITE_MISS_COPY_TO_DEVICE_ENDIO";
	case CACHE_VALID_CLEAN_INVALIDATE_START:
		return "CACHE_VALID_CLEAN_INVALIDATE_START";
	case CACHE_VALID_CLEAN_INVALIDATE_END:
		return "CACHE_VALID_CLEAN_INVALIDATE_END";
	case CACHE_VALID_CLEAN_VERIFY:
		return "CACHE_VALID_CLEAN_VERIFY";
	case CACHE_VALID_DIRTY:
		return "CACHE_VALID_DIRTY";
	case CACHE_VALID_DIRTY_NO_DATA:
		return "CACHE_VALID_DIRTY_NO_DATA";
	case CACHE_VALID_DIRTY_READ_HIT_COPY_FROM_CACHE_START:
		return "CACHE_VALID_DIRTY_READ_HIT_COPY_FROM_CACHE_START";
	case CACHE_VALID_DIRTY_READ_HIT_COPY_FROM_CACHE_END:
		return "CACHE_VALID_DIRTY_READ_HIT_COPY_FROM_CACHE_END";
	case CACHE_VALID_DIRTY_WRITE_MISS_COPY_TO_CACHE_START:
		return "CACHE_VALID_DIRTY_WRITE_MISS_COPY_TO_CACHE_START";
	case CACHE_VALID_DIRTY_WRITE_MISS_COPY_TO_CACHE_END:
		return "CACHE_VALID_DIRTY_WRITE_MISS_COPY_TO_CACHE_END";
	case CACHE_VALID_DIRTY_WRITE_HIT_COPY_TO_CACHE_START:
		return "CACHE_VALID_DIRTY_WRITE_HIT_COPY_TO_CACHE_START";
	case CACHE_VALID_DIRTY_WRITE_HIT_COPY_TO_CACHE_END:
		return "CACHE_VALID_DIRTY_WRITE_HIT_COPY_TO_CACHE_END";
	case CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_COPY_FROM_CACHE_START:
		return
		    "CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_COPY_FROM_CACHE_START";
	case CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_COPY_TO_CACHE_START:
		return
		    "CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_COPY_TO_CACHE_START";
	case CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_COPY_TO_CACHE_END:
		return "CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_COPY_TO_CACHE_END";
	case CACHE_VALID_DIRTY_WRITE_HIT_DWC_COPY_TO_CACHE_START:
		return "CACHE_VALID_DIRTY_WRITE_HIT_DWC_COPY_TO_CACHE_START";
	case CACHE_VALID_DIRTY_WRITE_HIT_DWC_COPY_TO_CACHE_END:
		return "CACHE_VALID_DIRTY_WRITE_HIT_DWC_COPY_TO_CACHE_END";
	case CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_DWC_COPY_FROM_ORIGINAL_CACHE_START:
		return
		    "CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_DWC_COPY_FROM_ORIGINAL_CACHE_START";
	case CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_DWC_COPY_TO_CLONED_CACHE_START:
		return
		    "CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_DWC_COPY_TO_CLONED_CACHE_START";
	case CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_DWC_COPY_TO_CLONED_CACHE_END:
		return
		    "CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_DWC_COPY_TO_CLONED_CACHE_END";
	case CACHE_VALID_DIRTY_PARTIAL_WRITE_MISS_COPY_FROM_DEVICE_STARTIO:
		return
		    "CACHE_VALID_DIRTY_PARTIAL_WRITE_MISS_COPY_FROM_DEVICE_STARTIO";
	case CACHE_VALID_DIRTY_PARTIAL_WRITE_MISS_COPY_FROM_DEVICE_ENDIO:
		return
		    "CACHE_VALID_DIRTY_PARTIAL_WRITE_MISS_COPY_FROM_DEVICE_ENDIO";
	case CACHE_VALID_DIRTY_PARTIAL_WRITE_MISS_COPY_TO_CACHE_END:
		return "CACHE_VALID_DIRTY_PARTIAL_WRITE_MISS_COPY_TO_CACHE_END";
	case CACHE_VALID_DIRTY_WRITEBACK_COPY_FROM_CACHE_START:
		return "CACHE_VALID_DIRTY_WRITEBACK_COPY_FROM_CACHE_START";
	case CACHE_VALID_DIRTY_WRITEBACK_COPY_FROM_CACHE_END:
		return "CACHE_VALID_DIRTY_WRITEBACK_COPY_FROM_CACHE_END";
	case CACHE_VALID_DIRTY_WRITEBACK_COPY_TO_DEVICE_ENDIO:
		return "CACHE_VALID_DIRTY_WRITEBACK_COPY_TO_DEVICE_ENDIO";
	case CACHE_VALID_DIRTY_WRITEBACK_UPDATE_METADATA_END:
		return "CACHE_VALID_DIRTY_WRITEBACK_UPDATE_METADATA_END";
	case CACHE_VALID_DIRTY_WRITEBACK_INV_COPY_FROM_CACHE_START:
		return "CACHE_VALID_DIRTY_WRITEBACK_INV_COPY_FROM_CACHE_START";
	case CACHE_VALID_DIRTY_WRITEBACK_INV_COPY_FROM_CACHE_END:
		return "CACHE_VALID_DIRTY_WRITEBACK_INV_COPY_FROM_CACHE_END";
	case CACHE_VALID_DIRTY_WRITEBACK_INV_COPY_TO_DEVICE_ENDIO:
		return "CACHE_VALID_DIRTY_WRITEBACK_INV_COPY_TO_DEVICE_ENDIO";
	case CACHE_VALID_DIRTY_WRITEBACK_INV_UPDATE_METADATA_END:
		return "CACHE_VALID_DIRTY_WRITEBACK_INV_UPDATE_METADATA_END";
	case CACHE_VALID_DIRTY_INVALIDATE_START:
		return "CACHE_VALID_DIRTY_INVALIDATE_START";
	case CACHE_VALID_DIRTY_INVALIDATE_END:
		return "CACHE_VALID_DIRTY_INVALIDATE_END";
	case __CACHE_STATES_NUM:
		break;
	}
	return "CACHE_UNKNOWN";
}

const char *transition_path_to_str(enum
						 transition_path
						 path)
{
	switch (path) {
	case CACHE_TRANSITION_PATH_NONE:
		return "PATH_NONE";
	case CACHE_TRANSITION_PATH_READ_MISS_WTWB_CLEAN:
		return "PATH_READ_MISS_WTWB_CLEAN";
	case CACHE_TRANSITION_PATH_READ_HIT_WTWB_CLEAN:
		return "PATH_READ_HIT_WTWB_CLEAN";
	case CACHE_TRANSITION_PATH_READ_HIT_WB_DIRTY:
		return "PATH_READ_HIT_WB_DIRTY";
	case CACHE_TRANSITION_PATH_WRITE_MISS_WT:
		return "PATH_WRITE_MISS_WT";
	case CACHE_TRANSITION_PATH_WRITE_MISS_WB:
		return "PATH_WRITE_MISS_WB";
	case CACHE_TRANSITION_PATH_WRITE_HIT_WT:
		return "PATH_WRITE_HIT_WT";
	case CACHE_TRANSITION_PATH_PARTIAL_WRITE_HIT_WT:
		return "PATH_PARTIAL_WRITE_HIT_WT";
	case CACHE_TRANSITION_PATH_WRITE_HIT_WB_CLEAN:
		return "PATH_WRITE_HIT_WB_CLEAN";
	case CACHE_TRANSITION_PATH_PARTIAL_WRITE_HIT_WB_CLEAN:
		return "PATH_PARTIAL_WRITE_HIT_WB_CLEAN";
	case CACHE_TRANSITION_PATH_PARTIAL_WRITE_HIT_WB_DIRTY_DWC_CLONE:
		return
		    "PATH_PARTIAL_WRITE_HIT_WB_DIRTY_DWC_CLONE";
	case CACHE_TRANSITION_PATH_WRITE_HIT_WB_DIRTY_DWC_CLONE:
		return "PATH_WRITE_HIT_WB_DIRTY_DWC_CLONE";
	case CACHE_TRANSITION_PATH_PARTIAL_WRITE_MISS_WT:
		return "PATH_PARTIAL_WRITE_MISS_WT";
	case CACHE_TRANSITION_PATH_PARTIAL_WRITE_MISS_WB:
		return "PATH_PARTIAL_WRITE_MISS_WB";
	case CACHE_TRANSITION_PATH_WRITEBACK_WB:
		return "PATH_WRITEBACK_WB";
	case CACHE_TRANSITION_PATH_WRITEBACK_INV_WB:
		return "PATH_WRITEBACK_INV_WB";
	case CACHE_TRANSITION_PATH_CLEAN_INVALIDATION_WTWB:
		return "PATH_CLEAN_INVALIDATION_WTWB";
	case CACHE_TRANSITION_PATH_DIRTY_INVALIDATION_WB:
		return "PATH_DIRTY_INVALIDATION_WB";
	case CACHE_TRANSITION_PATH_VERIFY_CLEAN_WTWB:
		return "PATH_VERIFY_CLEAN_WTWB";
	case __CACHE_TRANSITION_PATHS_NUM:
		break;
	}
	return "PATH_UNKNOWN";
}

#ifdef ENABLE_ASSERT

struct cache_state_transitions {
	enum transition_path path_from;
	enum cache_state state_from;
	enum transition_path path_to;
	enum cache_state state_to;
};

const struct cache_state_transitions cache_valid_state_transitions[] = {
/*
 * read miss (wt/wb-clean):
 * INVALID -->
 * VALID_CLEAN_NO_DATA -->
 * VALID_CLEAN_READ_MISS_COPY_FROM_DEVICE_STARTIO -->
 * VALID_CLEAN_READ_MISS_COPY_FROM_DEVICE_ENDIO -->
 * VALID_CLEAN_READ_MISS_COPY_TO_CACHE_END -->
 * VALID_CLEAN
 */
	{
	 CACHE_TRANSITION_PATH_NONE,
	 CACHE_VALID_CLEAN_NO_DATA,
	 CACHE_TRANSITION_PATH_READ_MISS_WTWB_CLEAN,
	 CACHE_VALID_CLEAN_READ_MISS_COPY_FROM_DEVICE_STARTIO,
	 },
	{
	 CACHE_TRANSITION_PATH_READ_MISS_WTWB_CLEAN,
	 CACHE_VALID_CLEAN_READ_MISS_COPY_FROM_DEVICE_STARTIO,
	 CACHE_TRANSITION_PATH_READ_MISS_WTWB_CLEAN,
	 CACHE_VALID_CLEAN_READ_MISS_COPY_FROM_DEVICE_ENDIO,
	 },
	{
	 CACHE_TRANSITION_PATH_READ_MISS_WTWB_CLEAN,
	 CACHE_VALID_CLEAN_READ_MISS_COPY_FROM_DEVICE_ENDIO,
	 CACHE_TRANSITION_PATH_READ_MISS_WTWB_CLEAN,
	 CACHE_VALID_CLEAN_READ_MISS_COPY_TO_CACHE_END,
	 },
	{
	 CACHE_TRANSITION_PATH_READ_MISS_WTWB_CLEAN,
	 CACHE_VALID_CLEAN_READ_MISS_COPY_TO_CACHE_END,
	 CACHE_TRANSITION_PATH_NONE,
	 CACHE_VALID_CLEAN,
	 },

/*
 * read hit (wt/wb-clean):      VALID_CLEAN -->
 *                              VALID_CLEAN_READ_HIT_COPY_FROM_CACHE_START -->
 *                              VALID_CLEAN_READ_HIT_COPY_FROM_CACHE_END -->
 *                              VALID_CLEAN
 */
	{
	 CACHE_TRANSITION_PATH_NONE,
	 CACHE_VALID_CLEAN,
	 CACHE_TRANSITION_PATH_READ_HIT_WTWB_CLEAN,
	 CACHE_VALID_CLEAN_READ_HIT_COPY_FROM_CACHE_START,
	 },
	{
	 CACHE_TRANSITION_PATH_READ_HIT_WTWB_CLEAN,
	 CACHE_VALID_CLEAN_READ_HIT_COPY_FROM_CACHE_START,
	 CACHE_TRANSITION_PATH_READ_HIT_WTWB_CLEAN,
	 CACHE_VALID_CLEAN_READ_HIT_COPY_FROM_CACHE_END,
	 },
	{
	 CACHE_TRANSITION_PATH_READ_HIT_WTWB_CLEAN,
	 CACHE_VALID_CLEAN_READ_HIT_COPY_FROM_CACHE_END,
	 CACHE_TRANSITION_PATH_NONE,
	 CACHE_VALID_CLEAN,
	 },
/*
 * read hit (wb-dirty):         VALID_DIRTY -->
 *                              VALID_DIRTY_READ_HIT_COPY_FROM_CACHE_START -->
 *                              VALID_DIRTY_READ_HIT_COPY_FROM_CACHE_END -->
 *                              VALID_DIRTY
 */
	{
	 CACHE_TRANSITION_PATH_NONE,
	 CACHE_VALID_DIRTY,
	 CACHE_TRANSITION_PATH_READ_HIT_WB_DIRTY,
	 CACHE_VALID_DIRTY_READ_HIT_COPY_FROM_CACHE_START,
	 },
	{
	 CACHE_TRANSITION_PATH_READ_HIT_WB_DIRTY,
	 CACHE_VALID_DIRTY_READ_HIT_COPY_FROM_CACHE_START,
	 CACHE_TRANSITION_PATH_READ_HIT_WB_DIRTY,
	 CACHE_VALID_DIRTY_READ_HIT_COPY_FROM_CACHE_END,
	 },
	{
	 CACHE_TRANSITION_PATH_READ_HIT_WB_DIRTY,
	 CACHE_VALID_DIRTY_READ_HIT_COPY_FROM_CACHE_END,
	 CACHE_TRANSITION_PATH_NONE,
	 CACHE_VALID_DIRTY,
	 },
/*
 * write miss (wt):
 * INVALID -->
 * VALID_CLEAN_NO_DATA -->
 * VALID_CLEAN_WRITE_MISS_COPY_TO_DEVICE_STARTIO -->
 * VALID_CLEAN_WRITE_MISS_COPY_TO_DEVICE_ENDIO -->
 * VALID_CLEAN_WRITE_MISS_COPY_TO_CACHE_END -->
 * VALID_CLEAN
 */
	{
	 CACHE_TRANSITION_PATH_NONE,
	 CACHE_VALID_CLEAN_NO_DATA,
	 CACHE_TRANSITION_PATH_WRITE_MISS_WT,
	 CACHE_VALID_CLEAN_WRITE_MISS_COPY_TO_DEVICE_STARTIO,
	 },
	{
	 CACHE_TRANSITION_PATH_WRITE_MISS_WT,
	 CACHE_VALID_CLEAN_WRITE_MISS_COPY_TO_DEVICE_STARTIO,
	 CACHE_TRANSITION_PATH_WRITE_MISS_WT,
	 CACHE_VALID_CLEAN_WRITE_MISS_COPY_TO_DEVICE_ENDIO,
	 },
	{
	 CACHE_TRANSITION_PATH_WRITE_MISS_WT,
	 CACHE_VALID_CLEAN_WRITE_MISS_COPY_TO_DEVICE_ENDIO,
	 CACHE_TRANSITION_PATH_WRITE_MISS_WT,
	 CACHE_VALID_CLEAN_WRITE_MISS_COPY_TO_CACHE_END,
	 },
	{
	 CACHE_TRANSITION_PATH_WRITE_MISS_WT,
	 CACHE_VALID_CLEAN_WRITE_MISS_COPY_TO_CACHE_END,
	 CACHE_TRANSITION_PATH_NONE,
	 CACHE_VALID_CLEAN,
	 },
/*
 * write miss (wb):             INVALID -->
 *                              VALID_DIRTY_NO_DATA -->
 *                              VALID_DIRTY_WRITE_MISS_COPY_TO_CACHE_START -->
 *                              VALID_DIRTY_WRITE_MISS_COPY_TO_CACHE_END -->
 *                              VALID_DIRTY
 */
	{
	 CACHE_TRANSITION_PATH_NONE,
	 CACHE_VALID_DIRTY_NO_DATA,
	 CACHE_TRANSITION_PATH_WRITE_MISS_WB,
	 CACHE_VALID_DIRTY_WRITE_MISS_COPY_TO_CACHE_START,
	 },
	{
	 CACHE_TRANSITION_PATH_WRITE_MISS_WB,
	 CACHE_VALID_DIRTY_WRITE_MISS_COPY_TO_CACHE_START,
	 CACHE_TRANSITION_PATH_WRITE_MISS_WB,
	 CACHE_VALID_DIRTY_WRITE_MISS_COPY_TO_CACHE_END,
	 },
	{
	 CACHE_TRANSITION_PATH_WRITE_MISS_WB,
	 CACHE_VALID_DIRTY_WRITE_MISS_COPY_TO_CACHE_END,
	 CACHE_TRANSITION_PATH_NONE,
	 CACHE_VALID_DIRTY,
	 },
/*
 * [ write hit (wt) ] uses the same states as [ write miss (wb) ]
 * write hit (wt):
 * VALID_CLEAN -->
 * VALID_CLEAN_WRITE_HIT_COPY_TO_DEVICE_STARTIO  -->
 * VALID_CLEAN_WRITE_HIT_COPY_TO_DEVICE_ENDIO  -->
 * VALID_CLEAN_WRITE_HIT_COPY_TO_CACHE_END -->
 * VALID_CLEAN
 */
	{
	 CACHE_TRANSITION_PATH_NONE,
	 CACHE_VALID_CLEAN,
	 CACHE_TRANSITION_PATH_WRITE_HIT_WT,
	 CACHE_VALID_CLEAN_WRITE_HIT_COPY_TO_DEVICE_STARTIO,
	 },
	{
	 CACHE_TRANSITION_PATH_WRITE_HIT_WT,
	 CACHE_VALID_CLEAN_WRITE_HIT_COPY_TO_DEVICE_STARTIO,
	 CACHE_TRANSITION_PATH_WRITE_HIT_WT,
	 CACHE_VALID_CLEAN_WRITE_HIT_COPY_TO_DEVICE_ENDIO,
	 },
	{
	 CACHE_TRANSITION_PATH_WRITE_HIT_WT,
	 CACHE_VALID_CLEAN_WRITE_HIT_COPY_TO_DEVICE_ENDIO,
	 CACHE_TRANSITION_PATH_WRITE_HIT_WT,
	 CACHE_VALID_CLEAN_WRITE_HIT_COPY_TO_CACHE_END,
	 },
	{
	 CACHE_TRANSITION_PATH_WRITE_HIT_WT,
	 CACHE_VALID_CLEAN_WRITE_HIT_COPY_TO_CACHE_END,
	 CACHE_TRANSITION_PATH_NONE,
	 CACHE_VALID_CLEAN,
	 },
/*
 * [ partial write hit (wt) ] uses the same states as [ write miss (wb) ] plus
 * the initial copy-from-cache phase
 * write hit (wt):
 * VALID_CLEAN -->
 * VALID_CLEAN_PARTIAL_WRITE_HIT_COPY_FROM_CACHE_START -->
 * VALID_CLEAN_PARTIAL_WRITE_HIT_COPY_TO_DEVICE_STARTIO  -->
 * VALID_CLEAN_PARTIAL_WRITE_HIT_COPY_TO_DEVICE_ENDIO  -->
 * VALID_CLEAN_PARTIAL_WRITE_HIT_COPY_TO_CACHE_END -->
 * VALID_CLEAN
 */
	{
	 CACHE_TRANSITION_PATH_NONE,
	 CACHE_VALID_CLEAN,
	 CACHE_TRANSITION_PATH_PARTIAL_WRITE_HIT_WT,
	 CACHE_VALID_CLEAN_PARTIAL_WRITE_HIT_COPY_FROM_CACHE_START,
	 },
	{
	 CACHE_TRANSITION_PATH_PARTIAL_WRITE_HIT_WT,
	 CACHE_VALID_CLEAN_PARTIAL_WRITE_HIT_COPY_FROM_CACHE_START,
	 CACHE_TRANSITION_PATH_PARTIAL_WRITE_HIT_WT,
	 CACHE_VALID_CLEAN_PARTIAL_WRITE_HIT_COPY_TO_DEVICE_STARTIO,
	 },
	{
	 CACHE_TRANSITION_PATH_PARTIAL_WRITE_HIT_WT,
	 CACHE_VALID_CLEAN_PARTIAL_WRITE_HIT_COPY_TO_DEVICE_STARTIO,
	 CACHE_TRANSITION_PATH_PARTIAL_WRITE_HIT_WT,
	 CACHE_VALID_CLEAN_PARTIAL_WRITE_HIT_COPY_TO_DEVICE_ENDIO,
	 },
	{
	 CACHE_TRANSITION_PATH_PARTIAL_WRITE_HIT_WT,
	 CACHE_VALID_CLEAN_PARTIAL_WRITE_HIT_COPY_TO_DEVICE_ENDIO,
	 CACHE_TRANSITION_PATH_PARTIAL_WRITE_HIT_WT,
	 CACHE_VALID_CLEAN_PARTIAL_WRITE_HIT_COPY_TO_CACHE_END,
	 },
	{
	 CACHE_TRANSITION_PATH_PARTIAL_WRITE_HIT_WT,
	 CACHE_VALID_CLEAN_PARTIAL_WRITE_HIT_COPY_TO_CACHE_END,
	 CACHE_TRANSITION_PATH_NONE,
	 CACHE_VALID_CLEAN,
	 },
/*
 * [ write hit (wb-clean) ] uses the same states as [ write miss (wb) ]
 * write hit (wb-clean):        VALID_CLEAN -->
 *                              VALID_DIRTY_WRITE_HIT_COPY_TO_CACHE_START -->
 *                              VALID_DIRTY_WRITE_HIT_COPY_TO_CACHE_END -->
 *                              VALID_DIRTY
 */
	{
	 CACHE_TRANSITION_PATH_NONE,
	 CACHE_VALID_CLEAN,
	 CACHE_TRANSITION_PATH_WRITE_HIT_WB_CLEAN,
	 CACHE_VALID_DIRTY_WRITE_HIT_COPY_TO_CACHE_START,
	 },
	{
	 CACHE_TRANSITION_PATH_WRITE_HIT_WB_CLEAN,
	 CACHE_VALID_DIRTY_WRITE_HIT_COPY_TO_CACHE_START,
	 CACHE_TRANSITION_PATH_WRITE_HIT_WB_CLEAN,
	 CACHE_VALID_DIRTY_WRITE_HIT_COPY_TO_CACHE_END,
	 },
	{
	 CACHE_TRANSITION_PATH_WRITE_HIT_WB_CLEAN,
	 CACHE_VALID_DIRTY_WRITE_HIT_COPY_TO_CACHE_END,
	 CACHE_TRANSITION_PATH_NONE,
	 CACHE_VALID_DIRTY,
	 },
/*
 * [ partial write hit (wb-clean) ] uses the same states as [ write miss (wb) ]
 * plus the initial copy-from-cache phase
 * write hit (wb-clean):
 * VALID_CLEAN -->
 * VALID_DIRTY_PARTIAL_WRITE_HIT_COPY_FROM_CACHE_START -->
 * VALID_DIRTY_PARTIAL_WRITE_HIT_COPY_TO_CACHE_START -->
 * VALID_DIRTY_PARTIAL_WRITE_HIT_COPY_TO_CACHE_END -->
 * VALID_DIRTY
 */
	{
	 CACHE_TRANSITION_PATH_NONE,
	 CACHE_VALID_CLEAN,
	 CACHE_TRANSITION_PATH_PARTIAL_WRITE_HIT_WB_CLEAN,
	 CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_COPY_FROM_CACHE_START,
	 },
	{
	 CACHE_TRANSITION_PATH_PARTIAL_WRITE_HIT_WB_CLEAN,
	 CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_COPY_FROM_CACHE_START,
	 CACHE_TRANSITION_PATH_PARTIAL_WRITE_HIT_WB_CLEAN,
	 CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_COPY_TO_CACHE_START,
	 },
	{
	 CACHE_TRANSITION_PATH_PARTIAL_WRITE_HIT_WB_CLEAN,
	 CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_COPY_TO_CACHE_START,
	 CACHE_TRANSITION_PATH_PARTIAL_WRITE_HIT_WB_CLEAN,
	 CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_COPY_TO_CACHE_END,
	 },
	{
	 CACHE_TRANSITION_PATH_PARTIAL_WRITE_HIT_WB_CLEAN,
	 CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_COPY_TO_CACHE_END,
	 CACHE_TRANSITION_PATH_NONE,
	 CACHE_VALID_DIRTY,
	 },
/*
 * partial dirty write hit (dirty write cloning - clone):
 * VALID_DIRTY_NO_DATA -->
 * VALID_DIRTY_PARTIAL_WRITE_HIT_DWC_COPY_FROM_ORIGINAL_CACHE_START -->
 * VALID_DIRTY_PARTIAL_WRITE_HIT_DWC_COPY_TO_CLONED_CACHE_START -->
 * VALID_DIRTY_PARTIAL_WRITE_HIT_DWC_COPY_TO_CLONED_CACHE_END -->
 * VALID_DIRTY
 */
	{
	 CACHE_TRANSITION_PATH_NONE,
	 CACHE_VALID_DIRTY_NO_DATA,
	 CACHE_TRANSITION_PATH_PARTIAL_WRITE_HIT_WB_DIRTY_DWC_CLONE,
	 CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_DWC_COPY_FROM_ORIGINAL_CACHE_START,
	 },
	{
	 CACHE_TRANSITION_PATH_PARTIAL_WRITE_HIT_WB_DIRTY_DWC_CLONE,
	 CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_DWC_COPY_FROM_ORIGINAL_CACHE_START,
	 CACHE_TRANSITION_PATH_PARTIAL_WRITE_HIT_WB_DIRTY_DWC_CLONE,
	 CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_DWC_COPY_TO_CLONED_CACHE_START,
	 },
	{
	 CACHE_TRANSITION_PATH_PARTIAL_WRITE_HIT_WB_DIRTY_DWC_CLONE,
	 CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_DWC_COPY_TO_CLONED_CACHE_START,
	 CACHE_TRANSITION_PATH_PARTIAL_WRITE_HIT_WB_DIRTY_DWC_CLONE,
	 CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_DWC_COPY_TO_CLONED_CACHE_END,
	 },
	{
	 CACHE_TRANSITION_PATH_PARTIAL_WRITE_HIT_WB_DIRTY_DWC_CLONE,
	 CACHE_VALID_DIRTY_PARTIAL_WRITE_HIT_DWC_COPY_TO_CLONED_CACHE_END,
	 CACHE_TRANSITION_PATH_NONE,
	 CACHE_VALID_DIRTY,
	 },
/*
 * dirty write hit (dirty write cloning - clone):
 * VALID_DIRTY_NO_DATA -->
 * VALID_DIRTY_WRITE_HIT_DWC_COPY_TO_CACHE_START -->
 * VALID_DIRTY_WRITE_HIT_DWC_COPY_TO_CACHE_END -->
 * VALID_DIRTY
 */
	{
	 CACHE_TRANSITION_PATH_NONE,
	 CACHE_VALID_DIRTY_NO_DATA,
	 CACHE_TRANSITION_PATH_WRITE_HIT_WB_DIRTY_DWC_CLONE,
	 CACHE_VALID_DIRTY_WRITE_HIT_DWC_COPY_TO_CACHE_START,
	 },
	{
	 CACHE_TRANSITION_PATH_WRITE_HIT_WB_DIRTY_DWC_CLONE,
	 CACHE_VALID_DIRTY_WRITE_HIT_DWC_COPY_TO_CACHE_START,
	 CACHE_TRANSITION_PATH_WRITE_HIT_WB_DIRTY_DWC_CLONE,
	 CACHE_VALID_DIRTY_WRITE_HIT_DWC_COPY_TO_CACHE_END,
	 },
	{
	 CACHE_TRANSITION_PATH_WRITE_HIT_WB_DIRTY_DWC_CLONE,
	 CACHE_VALID_DIRTY_WRITE_HIT_DWC_COPY_TO_CACHE_END,
	 CACHE_TRANSITION_PATH_NONE,
	 CACHE_VALID_DIRTY,
	 },
/*
 * partial write miss (wt):
 * INVALID -->
 * VALID_CLEAN_NO_DATA -->
 * VALID_CLEAN_PARTIAL_WRITE_MISS_COPY_FROM_DEVICE_STARTIO -->
 * VALID_CLEAN_PARTIAL_WRITE_MISS_COPY_FROM_DEVICE_ENDIO -->
 * VALID_CLEAN_PARTIAL_WRITE_MISS_COPY_TO_DEVICE_ENDIO -->
 * VALID_CLEAN_PARTIAL_WRITE_MISS_COPY_TO_CACHE_END -->
 * VALID_CLEAN
 */
	{
	 CACHE_TRANSITION_PATH_NONE,
	 CACHE_VALID_CLEAN_NO_DATA,
	 CACHE_TRANSITION_PATH_PARTIAL_WRITE_MISS_WT,
	 CACHE_VALID_CLEAN_PARTIAL_WRITE_MISS_COPY_FROM_DEVICE_STARTIO,
	 },
	{
	 CACHE_TRANSITION_PATH_PARTIAL_WRITE_MISS_WT,
	 CACHE_VALID_CLEAN_PARTIAL_WRITE_MISS_COPY_FROM_DEVICE_STARTIO,
	 CACHE_TRANSITION_PATH_PARTIAL_WRITE_MISS_WT,
	 CACHE_VALID_CLEAN_PARTIAL_WRITE_MISS_COPY_FROM_DEVICE_ENDIO,
	 },
	{
	 CACHE_TRANSITION_PATH_PARTIAL_WRITE_MISS_WT,
	 CACHE_VALID_CLEAN_PARTIAL_WRITE_MISS_COPY_FROM_DEVICE_ENDIO,
	 CACHE_TRANSITION_PATH_PARTIAL_WRITE_MISS_WT,
	 CACHE_VALID_CLEAN_PARTIAL_WRITE_MISS_COPY_TO_DEVICE_ENDIO,
	 },
	{
	 CACHE_TRANSITION_PATH_PARTIAL_WRITE_MISS_WT,
	 CACHE_VALID_CLEAN_PARTIAL_WRITE_MISS_COPY_TO_DEVICE_ENDIO,
	 CACHE_TRANSITION_PATH_PARTIAL_WRITE_MISS_WT,
	 CACHE_VALID_CLEAN_PARTIAL_WRITE_MISS_COPY_TO_CACHE_END,
	 },
	{
	 CACHE_TRANSITION_PATH_PARTIAL_WRITE_MISS_WT,
	 CACHE_VALID_CLEAN_PARTIAL_WRITE_MISS_COPY_TO_CACHE_END,
	 CACHE_TRANSITION_PATH_NONE,
	 CACHE_VALID_CLEAN,
	 },
/*
 * partial write miss (wb):
 * INVALID -->
 * VALID_DIRTY_NO_DATA -->
 * VALID_DIRTY_PARTIAL_WRITE_MISS_COPY_FROM_DEVICE_STARTIO -->
 * VALID_DIRTY_PARTIAL_WRITE_MISS_COPY_FROM_DEVICE_ENDIO -->
 * VALID_DIRTY_PARTIAL_WRITE_MISS_COPY_TO_CACHE_END -->
 */
	{
	 CACHE_TRANSITION_PATH_NONE,
	 CACHE_VALID_DIRTY_NO_DATA,
	 CACHE_TRANSITION_PATH_PARTIAL_WRITE_MISS_WB,
	 CACHE_VALID_DIRTY_PARTIAL_WRITE_MISS_COPY_FROM_DEVICE_STARTIO,
	 },
	{
	 CACHE_TRANSITION_PATH_PARTIAL_WRITE_MISS_WB,
	 CACHE_VALID_DIRTY_PARTIAL_WRITE_MISS_COPY_FROM_DEVICE_STARTIO,
	 CACHE_TRANSITION_PATH_PARTIAL_WRITE_MISS_WB,
	 CACHE_VALID_DIRTY_PARTIAL_WRITE_MISS_COPY_FROM_DEVICE_ENDIO,
	 },
	{
	 CACHE_TRANSITION_PATH_PARTIAL_WRITE_MISS_WB,
	 CACHE_VALID_DIRTY_PARTIAL_WRITE_MISS_COPY_FROM_DEVICE_ENDIO,
	 CACHE_TRANSITION_PATH_PARTIAL_WRITE_MISS_WB,
	 CACHE_VALID_DIRTY_PARTIAL_WRITE_MISS_COPY_TO_CACHE_END,
	 },
	{
	 CACHE_TRANSITION_PATH_PARTIAL_WRITE_MISS_WB,
	 CACHE_VALID_DIRTY_PARTIAL_WRITE_MISS_COPY_TO_CACHE_END,
	 CACHE_TRANSITION_PATH_NONE,
	 CACHE_VALID_DIRTY,
	 },
/*
 * verify (clean-wt/wb):        VALID_CLEAN -->
 *                              CACHE_VALID_CLEAN_VERIFY -->
 *                              VALID_CLEAN
 */
	{
	 CACHE_TRANSITION_PATH_NONE,
	 CACHE_VALID_CLEAN,
	 CACHE_TRANSITION_PATH_VERIFY_CLEAN_WTWB,
	 CACHE_VALID_CLEAN_VERIFY,
	 },
	{
	 CACHE_TRANSITION_PATH_VERIFY_CLEAN_WTWB,
	 CACHE_VALID_CLEAN_VERIFY,
	 CACHE_TRANSITION_PATH_NONE,
	 CACHE_VALID_CLEAN,
	 },
/*
 * writeback_flush (wb):        VALID_DIRTY -->
 *                              VALID_DIRTY_WRITEBACK_COPY_FROM_CACHE_START -->
 *                              VALID_DIRTY_WRITEBACK_COPY_FROM_CACHE_END -->
 *                              VALID_DIRTY_WRITEBACK_COPY_TO_DEVICE_ENDIO -->
 *                              VALID_DIRTY_WRITEBACK_UPDATE_METADATA_END -->
 *                              VALID_CLEAN
 */
	{
	 CACHE_TRANSITION_PATH_NONE,
	 CACHE_VALID_DIRTY,
	 CACHE_TRANSITION_PATH_WRITEBACK_WB,
	 CACHE_VALID_DIRTY_WRITEBACK_COPY_FROM_CACHE_START,
	 },
	{
	 CACHE_TRANSITION_PATH_WRITEBACK_WB,
	 CACHE_VALID_DIRTY_WRITEBACK_COPY_FROM_CACHE_START,
	 CACHE_TRANSITION_PATH_WRITEBACK_WB,
	 CACHE_VALID_DIRTY_WRITEBACK_COPY_FROM_CACHE_END,
	 },
	{
	 CACHE_TRANSITION_PATH_WRITEBACK_WB,
	 CACHE_VALID_DIRTY_WRITEBACK_COPY_FROM_CACHE_END,
	 CACHE_TRANSITION_PATH_WRITEBACK_WB,
	 CACHE_VALID_DIRTY_WRITEBACK_COPY_TO_DEVICE_ENDIO,
	 },
	{
	 CACHE_TRANSITION_PATH_WRITEBACK_WB,
	 CACHE_VALID_DIRTY_WRITEBACK_COPY_TO_DEVICE_ENDIO,
	 CACHE_TRANSITION_PATH_WRITEBACK_WB,
	 CACHE_VALID_DIRTY_WRITEBACK_UPDATE_METADATA_END,
	 },
	{
	 CACHE_TRANSITION_PATH_WRITEBACK_WB,
	 CACHE_VALID_DIRTY_WRITEBACK_UPDATE_METADATA_END,
	 CACHE_TRANSITION_PATH_NONE,
	 CACHE_VALID_CLEAN,
	 },
/*
 * writeback_invalidate (wb):
 * VALID_DIRTY -->
 * VALID_DIRTY_WRITEBACK_INV_COPY_FROM_CACHE_START -->
 * VALID_DIRTY_WRITEBACK_INV_COPY_FROM_CACHE_END -->
 * VALID_DIRTY_WRITEBACK_INV_COPY_TO_DEVICE_ENDIO -->
 * VALID_DIRTY_WRITEBACK_INV_UPDATE_METADATA_END -->
 * VALID_CLEAN
 */
	{
	 CACHE_TRANSITION_PATH_NONE,
	 CACHE_VALID_DIRTY,
	 CACHE_TRANSITION_PATH_WRITEBACK_INV_WB,
	 CACHE_VALID_DIRTY_WRITEBACK_INV_COPY_FROM_CACHE_START,
	 },
	{
	 CACHE_TRANSITION_PATH_WRITEBACK_INV_WB,
	 CACHE_VALID_DIRTY_WRITEBACK_INV_COPY_FROM_CACHE_START,
	 CACHE_TRANSITION_PATH_WRITEBACK_INV_WB,
	 CACHE_VALID_DIRTY_WRITEBACK_INV_COPY_FROM_CACHE_END,
	 },
	{
	 CACHE_TRANSITION_PATH_WRITEBACK_INV_WB,
	 CACHE_VALID_DIRTY_WRITEBACK_INV_COPY_FROM_CACHE_END,
	 CACHE_TRANSITION_PATH_WRITEBACK_INV_WB,
	 CACHE_VALID_DIRTY_WRITEBACK_INV_COPY_TO_DEVICE_ENDIO,
	 },
	{
	 CACHE_TRANSITION_PATH_WRITEBACK_INV_WB,
	 CACHE_VALID_DIRTY_WRITEBACK_INV_COPY_TO_DEVICE_ENDIO,
	 CACHE_TRANSITION_PATH_WRITEBACK_INV_WB,
	 CACHE_VALID_DIRTY_WRITEBACK_INV_UPDATE_METADATA_END,
	 },
	{
	 CACHE_TRANSITION_PATH_WRITEBACK_INV_WB,
	 CACHE_VALID_DIRTY_WRITEBACK_INV_UPDATE_METADATA_END,
	 CACHE_TRANSITION_PATH_NONE,
	 CACHE_INVALID,
	 },
/*
 * clean invalidation (wt/wb):  VALID_CLEAN -->
 *                              VALID_CLEAN_INVALIDATE_START -->
 *                              VALID_CLEAN_INVALIDATE_END -->
 *                              INVALID
 */
	{
	 CACHE_TRANSITION_PATH_NONE,
	 CACHE_VALID_CLEAN,
	 CACHE_TRANSITION_PATH_CLEAN_INVALIDATION_WTWB,
	 CACHE_VALID_CLEAN_INVALIDATE_START,
	 },
	{
	 CACHE_TRANSITION_PATH_CLEAN_INVALIDATION_WTWB,
	 CACHE_VALID_CLEAN_INVALIDATE_START,
	 CACHE_TRANSITION_PATH_CLEAN_INVALIDATION_WTWB,
	 CACHE_VALID_CLEAN_INVALIDATE_END,
	 },
	{
	 CACHE_TRANSITION_PATH_CLEAN_INVALIDATION_WTWB,
	 CACHE_VALID_CLEAN_INVALIDATE_END,
	 CACHE_TRANSITION_PATH_NONE,
	 CACHE_INVALID,
	 },
/*
 * dirty invalidation (wb):     VALID_DIRTY -->
 *                              VALID_DIRTY_INVALIDATE_START -->
 *                              VALID_DIRTY_INVALIDATE_END -->
 *                              INVALID
 */
	{
	 CACHE_TRANSITION_PATH_NONE,
	 CACHE_VALID_DIRTY,
	 CACHE_TRANSITION_PATH_DIRTY_INVALIDATION_WB,
	 CACHE_VALID_DIRTY_INVALIDATE_START,
	 },
	{
	 CACHE_TRANSITION_PATH_DIRTY_INVALIDATION_WB,
	 CACHE_VALID_DIRTY_INVALIDATE_START,
	 CACHE_TRANSITION_PATH_DIRTY_INVALIDATION_WB,
	 CACHE_VALID_DIRTY_INVALIDATE_END,
	 },
	{
	 CACHE_TRANSITION_PATH_DIRTY_INVALIDATION_WB,
	 CACHE_VALID_DIRTY_INVALIDATE_END,
	 CACHE_TRANSITION_PATH_NONE,
	 CACHE_INVALID,
	 },
};

#define CACHE_VALID_STATE_TRANSITIONS \
	(int)(sizeof(cache_valid_state_transitions) / \
	sizeof(struct cache_state_transitions))

int __cache_validate_state_transition(struct bittern_cache *bc,
					      struct cache_block
					      *cache_block,
					      const char *___function,
					      int ___line,
					      enum transition_path
					      p_from,
					      enum cache_state s_from,
					      enum transition_path
					      p_to,
					      enum cache_state s_to)
{
	int i;

	ASSERT_BITTERN_CACHE(bc);
	ASSERT_CACHE_BLOCK(cache_block, bc);
	ASSERT(CACHE_TRANSITION_PATH_VALID(p_from));
	ASSERT(CACHE_TRANSITION_PATH_VALID(p_to));
	ASSERT(CACHE_STATE_VALID(s_from));
	ASSERT(CACHE_STATE_VALID(s_to));

	for (i = 0; i < CACHE_VALID_STATE_TRANSITIONS; i++) {
		if (p_from == cache_valid_state_transitions[i].path_from
		    && s_from ==
		    cache_valid_state_transitions[i].state_from
		    && p_to == cache_valid_state_transitions[i].path_to
		    && s_to ==
		    cache_valid_state_transitions[i].state_to) {
			BT_TRACE(BT_LEVEL_TRACE1, bc, NULL, cache_block, NULL,
				 NULL,
				 "%s@%d(): valid-state-transition[%d/%d]: (%s,%s) -> (%s,%s)",
				 ___function, ___line, i,
				 CACHE_VALID_STATE_TRANSITIONS,
				 transition_path_to_str(p_from),
				 cache_state_to_str(s_from),
				 transition_path_to_str(p_to),
				 cache_state_to_str(s_to));
			ASSERT(p_from >= 0
			       && p_from <
			       __CACHE_TRANSITION_PATHS_NUM);
			ASSERT(s_from >= 0
			       && s_from < __CACHE_STATES_NUM);
			ASSERT(p_to >= 0
			       && p_to < __CACHE_TRANSITION_PATHS_NUM);
			ASSERT(s_to >= 0 && s_to < __CACHE_STATES_NUM);
			return 0;
		}
	}
	BT_TRACE(BT_LEVEL_ERROR, bc, NULL, cache_block, NULL, NULL,
		 "%s@%d(): invalid/unknown-state-transition: (%s,%s) -> (%s,%s)",
		 ___function, ___line,
		 transition_path_to_str(p_from),
		 cache_state_to_str(s_from),
		 transition_path_to_str(p_to),
		 cache_state_to_str(s_to));
	__printk_err(___function, ___line,
		     "invalid/unknown-state-transition: (%s,%s) -> (%s,%s)",
		     transition_path_to_str(p_from),
		     cache_state_to_str(s_from),
		     transition_path_to_str(p_to),
		     cache_state_to_str(s_to));
	return -1;
}

#endif /*ENABLE_ASSERT */

struct work_item *cache_work_item_allocate(struct bittern_cache *bc,
						   struct cache_block
						   *cache_block,
						   struct bio *bio,
						   int wi_flags,
						   wi_io_endio_f wi_io_endio,
						   int gfp_flags)
{
	struct work_item *wi;

	ASSERT_BITTERN_CACHE(bc);
	if (cache_block != NULL)
		ASSERT_CACHE_BLOCK(cache_block, bc);
	ASSERT((wi_flags & ~WI_FLAG_MASK) == 0);
	ASSERT((wi_flags & WI_FLAG_BIO_CLONED) != 0
	       || (wi_flags & WI_FLAG_BIO_NOT_CLONED) != 0);
	ASSERT((wi_flags & (WI_FLAG_BIO_CLONED | WI_FLAG_BIO_NOT_CLONED)) !=
	       (WI_FLAG_BIO_CLONED | WI_FLAG_BIO_NOT_CLONED));
	ASSERT((wi_flags & WI_FLAG_MAP_IO) != 0
	       || (wi_flags & WI_FLAG_WRITEBACK_IO) != 0
	       || (wi_flags & WI_FLAG_INVALIDATE_IO) != 0);
	ASSERT((wi_flags &
		(WI_FLAG_MAP_IO | WI_FLAG_WRITEBACK_IO | WI_FLAG_INVALIDATE_IO))
	       !=
	       (WI_FLAG_MAP_IO | WI_FLAG_WRITEBACK_IO | WI_FLAG_INVALIDATE_IO));
	ASSERT((wi_flags & WI_FLAG_XID_NEW) != 0
	       || (wi_flags & WI_FLAG_XID_USE_CACHE_BLOCK) != 0);
	ASSERT((wi_flags & (WI_FLAG_XID_NEW | WI_FLAG_XID_USE_CACHE_BLOCK)) !=
	       (WI_FLAG_XID_NEW | WI_FLAG_XID_USE_CACHE_BLOCK));
	ASSERT((wi_flags & WI_FLAG_WRITE_CLONING) == 0);
	ASSERT(gfp_flags == 0 || gfp_flags == GFP_NOIO
	       || gfp_flags == GFP_ATOMIC);
	if (gfp_flags == 0)
		gfp_flags = GFP_NOIO;
	wi = kmem_zalloc(sizeof(struct work_item), gfp_flags);
	M_ASSERT_FIXME(wi != NULL);
	wi->wi_magic1 = WI_MAGIC1;
	wi->wi_magic2 = WI_MAGIC2;
	wi->wi_magic3 = WI_MAGIC3;
	wi->wi_cache_block = cache_block;
	wi->wi_original_cache_block = NULL;
	wi->wi_original_bio = bio;
	wi->wi_flags = wi_flags;
	if (wi_flags & WI_FLAG_BIO_CLONED) {
		ASSERT(bio != NULL);
	} else {
		ASSERT((wi_flags & WI_FLAG_BIO_NOT_CLONED) != 0);
		ASSERT(bio == NULL);
		wi->wi_original_bio = NULL;
	}
	if ((wi_flags & WI_FLAG_XID_NEW) != 0) {
		ASSERT(cache_block == NULL);
		wi->wi_io_xid = cache_xid_inc(bc);
		wi->wi_cache_block = NULL;
	}
	if ((wi_flags & WI_FLAG_XID_USE_CACHE_BLOCK) != 0) {
		ASSERT(cache_block != NULL);
		wi->wi_io_xid = cache_block->bcb_xid;
	}
	ASSERT(wi->wi_io_xid != 0);
	if ((wi_flags & WI_FLAG_HAS_ENDIO) != 0) {
		ASSERT(wi_io_endio != NULL);
		wi->wi_io_endio = wi_io_endio;
	} else {
		ASSERT(wi_io_endio == NULL);
		wi->wi_io_endio = NULL;
	}
	wi->wi_cache = bc;
	INIT_LIST_HEAD(&wi->wi_deferred_io_list);
	INIT_LIST_HEAD(&wi->wi_pending_io_list);
	ASSERT_WORK_ITEM(wi, bc);

	wi->wi_cache_data.di_buffer_vmalloc_buffer = NULL;
	wi->wi_cache_data.di_buffer_vmalloc_page = NULL;
	wi->wi_cache_data.di_buffer_vmalloc_pool = -1;
	wi->wi_cache_data.di_buffer = NULL;
	wi->wi_cache_data.di_page = NULL;
	wi->wi_cache_data.di_flags = 0x0;
	atomic_set(&wi->wi_cache_data.di_busy, 0);

	return wi;
}

void cache_work_item_reallocate(struct bittern_cache *bc,
					struct cache_block *cache_block,
					struct work_item *wi,
					struct bio *bio,
					int wi_flags, wi_io_endio_f wi_io_endio)
{
	ASSERT_BITTERN_CACHE(bc);
	if (cache_block != NULL)
		ASSERT_CACHE_BLOCK(cache_block, bc);
	ASSERT((wi_flags & ~WI_FLAG_MASK) == 0);
	ASSERT((wi_flags & WI_FLAG_BIO_CLONED) != 0
	       || (wi_flags & WI_FLAG_BIO_NOT_CLONED) != 0);
	ASSERT((wi_flags & (WI_FLAG_BIO_CLONED | WI_FLAG_BIO_NOT_CLONED)) !=
	       (WI_FLAG_BIO_CLONED | WI_FLAG_BIO_NOT_CLONED));
	ASSERT((wi_flags & WI_FLAG_MAP_IO) != 0
	       || (wi_flags & WI_FLAG_WRITEBACK_IO) != 0
	       || (wi_flags & WI_FLAG_INVALIDATE_IO) != 0);
	ASSERT((wi_flags &
		(WI_FLAG_MAP_IO | WI_FLAG_WRITEBACK_IO | WI_FLAG_INVALIDATE_IO))
	       !=
	       (WI_FLAG_MAP_IO | WI_FLAG_WRITEBACK_IO | WI_FLAG_INVALIDATE_IO));
	ASSERT((wi_flags & WI_FLAG_XID_NEW) != 0
	       || (wi_flags & WI_FLAG_XID_USE_CACHE_BLOCK) != 0);
	ASSERT((wi_flags & (WI_FLAG_XID_NEW | WI_FLAG_XID_USE_CACHE_BLOCK)) !=
	       (WI_FLAG_XID_NEW | WI_FLAG_XID_USE_CACHE_BLOCK));
	ASSERT((wi_flags & WI_FLAG_WRITE_CLONING) == 0);

	ASSERT(wi != NULL);
	ASSERT_WORK_ITEM(wi, bc);

	wi->wi_cache_block = cache_block;
	wi->wi_original_cache_block = NULL;
	wi->wi_original_bio = bio;
	wi->wi_flags = wi_flags;
	if (wi_flags & WI_FLAG_BIO_CLONED) {
		ASSERT(bio != NULL);
	} else {
		ASSERT((wi_flags & WI_FLAG_BIO_NOT_CLONED) != 0);
		ASSERT(bio == NULL);
		wi->wi_original_bio = NULL;
	}
	if ((wi_flags & WI_FLAG_XID_NEW) != 0) {
		ASSERT(cache_block == NULL);
		wi->wi_io_xid = cache_xid_inc(bc);
		wi->wi_cache_block = NULL;
	}
	if ((wi_flags & WI_FLAG_XID_USE_CACHE_BLOCK) != 0) {
		ASSERT(cache_block != NULL);
		wi->wi_io_xid = cache_block->bcb_xid;
	}
	ASSERT(wi->wi_io_xid != 0);
	if ((wi_flags & WI_FLAG_HAS_ENDIO) != 0) {
		ASSERT(wi_io_endio != NULL);
		wi->wi_io_endio = wi_io_endio;
	} else {
		ASSERT(wi_io_endio == NULL);
		wi->wi_io_endio = NULL;
	}
	wi->wi_cache = bc;
	ASSERT(list_empty(&wi->wi_deferred_io_list));
	ASSERT(list_empty(&wi->wi_pending_io_list));
	ASSERT_WORK_ITEM(wi, bc);

	/* dbi_data is already set here */
	/*! \todo should pass dbi_data as param and set it? */
	/* wi->wi_cache_data.di_buffer_vmalloc_buffer = NULL; */
	/* wi->wi_cache_data.di_buffer_vmalloc_page = NULL; */
	/* wi->wi_cache_data.di_buffer_vmalloc_pool = -1; */
	ASSERT(wi->wi_cache_data.di_buffer == NULL);
	ASSERT(wi->wi_cache_data.di_page == NULL);
	ASSERT(wi->wi_cache_data.di_flags == 0x0);
	ASSERT(atomic_read(&wi->wi_cache_data.di_busy) == 0);
}

/*! \todo what if vmalloc buffer hasn't been allocated? */
void cache_work_item_free(struct bittern_cache *bc,
				  struct work_item *wi)
{
	ASSERT_BITTERN_CACHE(bc);
	ASSERT_WORK_ITEM(wi, bc);

	cache_work_item_del_pending_io(bc, wi);

	pagebuf_free_dbi(bc, &wi->wi_cache_data);

	ASSERT(wi->wi_cache_data.di_buffer_vmalloc_buffer == NULL);
	ASSERT(wi->wi_cache_data.di_buffer_vmalloc_page == NULL);
	ASSERT(wi->wi_cache_data.di_buffer_vmalloc_pool == -1);
	ASSERT(wi->wi_cache_data.di_buffer == NULL);
	ASSERT(wi->wi_cache_data.di_page == NULL);
	ASSERT(wi->wi_cache_data.di_flags == 0x0);
	ASSERT(atomic_read(&wi->wi_cache_data.di_busy) == 0);
	kmem_free(wi, sizeof(struct work_item));
}

/*!
 * \todo the caller uses the return value as "numbers of errors", which
 * is weird. we should think of a better way to do this.
 * \todo the name of this function is for sure poorly chosen.
 */
int __cache_verify_hash_data_ret(struct bittern_cache *bc,
				 struct cache_block *cache_block,
				 uint128_t hash_data,
				 const char *func,
				 int line)
{
	if (uint128_ne(hash_data, cache_block->bcb_hash_data)) {
		/*
		 * corrupt cache entry
		 */
		BT_TRACE(BT_LEVEL_TRACE0,
			 bc, NULL, cache_block, NULL, NULL,
			 "corrupt cache entry, hash=" UINT128_FMT ", computed_hash=" UINT128_FMT,
			 UINT128_ARG(cache_block->bcb_hash_data),
			 UINT128_ARG(hash_data));
		__printk_err(func,
			     line,
			     "corrupt hash id=#%d, cache_block=%lu, state=%d(%s), refcount=%d, hash=" UINT128_FMT ", computed_hash=" UINT128_FMT "\n",
			     cache_block->bcb_block_id,
			     cache_block->bcb_sector,
			     cache_block->bcb_state,
			     cache_state_to_str(cache_block->bcb_state),
			     atomic_read(&cache_block->bcb_refcount),
			     UINT128_ARG(cache_block->bcb_hash_data),
			     UINT128_ARG(hash_data));
		return 1;
	}
	return 0;
}

/*!
 * \todo the name of this function is for sure poorly chosen.
 */
int __cache_verify_hash_data_buffer_ret(struct bittern_cache *bc,
					struct cache_block *cache_block,
					void *buffer,
					const char *func,
					int line)
{
	uint128_t hash_data;

	hash_data = murmurhash3_128(buffer, PAGE_SIZE);
	return __cache_verify_hash_data_ret(bc,
					    cache_block,
					    hash_data,
					    func,
					    line);
}

/*!
 * caller uses this to "verify" the data hash, and expects
 * this function to assert if the data hash mismatches
 * \todo the name of this function is for sure poorly chosen.
 */
void __cache_verify_hash_data(struct bittern_cache *bc,
			      struct cache_block *cache_block,
			      uint128_t hash_data,
			      const char *func,
			      int line)
{
	__cache_verify_hash_data_ret(bc, cache_block, hash_data, func, line);
	M_ASSERT(uint128_eq(hash_data, cache_block->bcb_hash_data));
}

/*!
 * caller uses this to "verify" the data hash, and expects
 * this function to assert if the data hash mismatches
 * \todo the name of this function is for sure poorly chosen.
 */
void __cache_verify_hash_data_buffer(struct bittern_cache *bc,
				     struct cache_block *cache_block,
				     void *buffer,
				     const char *func,
				     int line)
{
	uint128_t hash_data;

	hash_data = murmurhash3_128(buffer, PAGE_SIZE);
	__cache_verify_hash_data_ret(bc, cache_block, hash_data, func, line);
	M_ASSERT(uint128_eq(hash_data, cache_block->bcb_hash_data));
}
