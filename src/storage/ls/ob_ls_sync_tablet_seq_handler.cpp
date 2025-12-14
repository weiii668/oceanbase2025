/**
 * Copyright (c) 2021 OceanBase
 * OceanBase CE is licensed under Mulan PubL v2.
 * You can use this software according to the terms and conditions of the Mulan PubL v2.
 * You may obtain a copy of Mulan PubL v2 at:
 *          http://license.coscl.org.cn/MulanPubL-2.0
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PubL v2 for more details.
 */

#define USING_LOG_PREFIX STORAGE
#include "storage/ls/ob_ls_sync_tablet_seq_handler.h"
#include "storage/ls/ob_ls.h"
#include "storage/ob_sync_tablet_seq_clog.h"
#include "logservice/ob_log_base_header.h"
#include "lib/oblog/ob_log_module.h"
#include "share/ob_tablet_autoincrement_service.h"

namespace oceanbase
{

using namespace share;
namespace storage
{

int ObLSSyncTabletSeqHandler::init(ObLS *ls)
{
  int ret = OB_SUCCESS;
  if (OB_UNLIKELY(is_inited_)) {
    ret = OB_INIT_TWICE;
    LOG_WARN("ObLSSyncTabletSeqHandler init twice", K(ret));
  } else if (OB_ISNULL(ls)) {
    ret = OB_INVALID_ARGUMENT;
    LOG_WARN("invalid argument", K(ret));
  } else {
    ls_ = ls;
    is_inited_ = true;
  }
  return ret;
}

void ObLSSyncTabletSeqHandler::reset()
{
  is_inited_ = false;
  ls_ = nullptr;
}

int ObLSSyncTabletSeqHandler::replay(const void *buffer,
                                     const int64_t nbytes,
                                     const palf::LSN &lsn,
                                     const int64_t ts_ns)
{
  int ret = OB_SUCCESS;
  logservice::ObLogBaseHeader base_header;
  ObSyncTabletSeqLog log;
  int64_t tmp_pos = 0;
  const char *log_buf = static_cast<const char *>(buffer);
  ObTabletAutoincSeqRpcHandler &autoinc_seq_handler = ObTabletAutoincSeqRpcHandler::get_instance();
  if (IS_NOT_INIT) {
    ret = OB_NOT_INIT;
    LOG_WARN("ObLSSyncTabletSeqHandler not inited", K(ret));
  } else if (OB_FAIL(base_header.deserialize(log_buf, nbytes, tmp_pos))) {
    LOG_WARN("log base header deserialize error", K(ret));
  } else if (OB_FAIL(log.deserialize(log_buf, nbytes, tmp_pos))) {
    LOG_WARN("ObSyncTabletSeqLog deserialize error", K(ret));
  } else if (OB_FAIL(autoinc_seq_handler.replay_update_tablet_autoinc_seq(ls_,
                                                                          log.get_tablet_id(),
                                                                          log.get_autoinc_seq(),
                                                                          ts_ns))) {
    LOG_WARN("failed to update tablet auto inc seq", K(ret), K(log));
  }
  return ret;
}

/**
 * @brief Forcefully switch to follower role
 * 
 * This function is called when the log stream (LS) is forced to switch to follower role.
 * It should clean up any leader-specific state and prepare for follower operations.
 * 
 * @note This function is currently not implemented.
 *       Implementation should handle cleanup of leader-specific resources.
 * 
 * @todo Implementation needed: Clean up leader-specific state when forced to follower
 */
void ObLSSyncTabletSeqHandler::switch_to_follower_forcedly()
{
  // TODO
}

/**
 * @brief Switch to leader role
 * 
 * This function is called when the log stream (LS) switches to leader role.
 * It should initialize any leader-specific state needed for tablet sequence synchronization.
 * 
 * @note This function is currently not implemented and returns OB_SUCCESS.
 *       Implementation should initialize leader-specific resources.
 * 
 * @return OB_SUCCESS on success, other error codes on failure
 * 
 * @todo Implementation needed: Initialize leader-specific state for tablet sequence sync
 */
int ObLSSyncTabletSeqHandler::switch_to_leader()
{
  int ret = OB_SUCCESS;

  //TODO

  return ret;
}

/**
 * @brief Gracefully switch to follower role
 * 
 * This function is called when the log stream (LS) gracefully switches to follower role.
 * It should save any necessary state before becoming a follower.
 * 
 * @note This function is currently not implemented and returns OB_SUCCESS.
 *       Implementation should save state before switching to follower.
 * 
 * @return OB_SUCCESS on success, other error codes on failure
 * 
 * @todo Implementation needed: Save state before gracefully switching to follower
 */
int ObLSSyncTabletSeqHandler::switch_to_follower_gracefully()
{
  int ret = OB_SUCCESS;

  //TODO

  return ret;
}

/**
 * @brief Resume leader role
 * 
 * This function is called when the log stream (LS) resumes the leader role.
 * It should restore any leader-specific state that was saved during graceful switch.
 * 
 * @note This function is currently not implemented and returns OB_SUCCESS.
 *       Implementation should restore leader-specific state.
 * 
 * @return OB_SUCCESS on success, other error codes on failure
 * 
 * @todo Implementation needed: Restore leader-specific state when resuming leader role
 */
int ObLSSyncTabletSeqHandler::resume_leader()
{
  int ret = OB_SUCCESS;

  //TODO

  return ret;
}

/**
 * @brief Flush checkpoint to persistent storage
 * 
 * This function is called to flush the checkpoint to persistent storage at the specified
 * log timestamp. It should persist the current state of tablet sequence synchronization.
 * 
 * @param rec_log_ts The log timestamp to flush checkpoint at
 * @return OB_SUCCESS on success, other error codes on failure
 * 
 * @note This function is currently not implemented and returns OB_SUCCESS.
 *       Implementation should persist checkpoint state.
 * 
 * @todo Implementation needed: Persist checkpoint state for tablet sequence sync
 */
int ObLSSyncTabletSeqHandler::flush(int64_t rec_log_ts)
{
  // TODO
  UNUSED(rec_log_ts);
  return OB_SUCCESS;
}

/**
 * @brief Get the recovery log timestamp
 * 
 * This function returns the log timestamp that can be used for recovery.
 * The returned timestamp should be the latest checkpoint that has been flushed.
 * 
 * @return The recovery log timestamp, or INT64_MAX if not available
 * 
 * @note This function is currently not implemented and returns INT64_MAX.
 *       Implementation should return the actual recovery log timestamp.
 * 
 * @todo Implementation needed: Return the actual recovery log timestamp from checkpoint
 */
int64_t ObLSSyncTabletSeqHandler::get_rec_log_ts()
{
  // TODO
  return INT64_MAX;
}

}
}
