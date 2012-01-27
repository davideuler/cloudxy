/*
 *  src/snapshot/hlfs_open_by_inode.c
 *
 *  Harry Wei <harryxiyou@gmail.com> (C) 2011
 *  Updated by Kelvin <kelvin.xupt@gmail.com>
 */
#include <stdio.h>
#include <stdint.h>
#include <glib.h>
#include <string.h>
#include "hlfs_ctrl.h"
#include "snapshot.h"
#include "storage_helper.h"
#include "comm_define.h"
#include "hlfs_log.h"

int hlfs_open_by_snapshot(struct hlfs_ctrl *ctrl,
					const char* snapshot,
					int flag) {
	HLOG_DEBUG("enter func %s", __func__);
	int ret = 0;
	struct snapshot *ss;
	if (0 > (ret = load_snapshot_by_name(storage, ss, sname))) {
		HLOG_ERROR("load ss by name error");
		g_free(ss);
		ret = -1;
		goto out;
	} else if (1 == ret) {
		HLOG_ERROR("We can not find the snapshot name");
		goto out;
	}
	struct inode *inode = load_inode(ctrl->storage,ss->inode_addr);
	if (inode == NULL) {
		HLOG_ERROR("load_inode error!");
		ret = -1;
		goto out;
	}

    ctrl->inode = inode;
    ctrl->imap_entry.inode_no = HLFS_INODE_NO;
    ctrl->inode_addr = inode_addr;

	if (0 == flag) {
		ctrl->rw_inode_flag = 0;
	} else if (1 == flag) {
		ctrl->rw_inode_flag = 1;
	} else {
		HLOG_ERROR("the bad flag for hlfs open by inode");
		ret = -1;
	}
    g_strlcpy(ctrl->alive_ss_name,ss->sname,strlen(ss->sname)+1);
    g_free(ss);
out:
	return ret;
	HLOG_DEBUG("leave func %s", __func__);
}