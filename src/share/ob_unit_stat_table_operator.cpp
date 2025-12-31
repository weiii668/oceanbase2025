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

#define USING_LOG_PREFIX SHARE

#include "share/ob_unit_stat_table_operator.h"
#include "share/schema/ob_multi_version_schema_service.h"
#include "share/schema/ob_table_schema.h"
#include "share/schema/ob_schema_getter_guard.h"
#include "share/schema/ob_part_mgr_util.h"
#include "share/inner_table/ob_inner_table_schema.h"
#include "observer/ob_server_struct.h" //GCTX

namespace oceanbase
{
using namespace common;
using namespace common::sqlclient;
using namespace share::schema;
namespace share
{
ObUnitStatTableOperator::ObUnitStatTableOperator()
  : inited_(false), check_stop_provider_(NULL)
{
}

ObUnitStatTableOperator::~ObUnitStatTableOperator()
{
}

int ObUnitStatTableOperator::init(share::ObCheckStopProvider &check_stop_provider)
{
  int ret = OB_SUCCESS;
  if (inited_) {
    ret = OB_INIT_TWICE;
    LOG_WARN("init twice", KR(ret));
  } else {
    check_stop_provider_ = &check_stop_provider;
    inited_ = true;
  }
  return ret;
}

/**
 * @brief Get unit statistics for a specific unit
 * 
 * This function retrieves unit statistics (including required_size and partition_cnt)
 * from the internal system tables for a given tenant and unit.
 * 
 * @note This function is currently not implemented and returns OB_SUCCESS.
 *       The implementation should query the internal system tables to populate
 *       the unit_stat structure with the unit's statistics information.
 * 
 * @param tenant_id The ID of the tenant
 * @param unit_id The ID of the unit to get statistics for
 * @param unit_stat Output parameter to store the unit statistics
 * @return OB_SUCCESS on success, other error codes on failure
 * 
 * @todo Implementation needed: Query internal system tables to get unit statistics
 */
int ObUnitStatTableOperator::get_unit_stat(uint64_t tenant_id,
                                           uint64_t unit_id,
                                           ObUnitStat &unit_stat) const
{
  UNUSEDx(tenant_id, unit_id, unit_stat);
  // TODO: @wanhong.wwh
  return 0;
}

/**
 * @brief Get unit statistics for all units in a tenant
 * 
 * This function retrieves unit statistics for all units belonging to a specific tenant
 * and populates the provided unit_stat_map with the results.
 * 
 * @note This function is currently not implemented and returns OB_SUCCESS.
 *       The implementation should query the internal system tables to get statistics
 *       for all units in the tenant and populate the unit_stat_map.
 * 
 * @param tenant_id The ID of the tenant
 * @param unit_stat_map Output parameter to store the map of unit statistics
 *                     (key: unit_id, value: ObUnitStat)
 * @return OB_SUCCESS on success, other error codes on failure
 * 
 * @todo Implementation needed: Query internal system tables to get all unit statistics
 *       for the tenant and populate the unit_stat_map
 */
int ObUnitStatTableOperator::get_unit_stat(uint64_t tenant_id,
                                           share::ObUnitStatMap &unit_stat_map) const
{
  UNUSEDx(tenant_id, unit_stat_map);
  // TODO: @wanhong.wwh
  return 0;
}


}//end namespace share
}//end namespace oceanbase
