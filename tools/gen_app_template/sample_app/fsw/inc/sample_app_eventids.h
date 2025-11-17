/************************************************************************
 * NASA Docket No. GSC-18,719-1, and identified as “core Flight System: Bootes”
 *
 * Copyright (c) 2020 United States Government as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License. You may obtain
 * a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ************************************************************************/

/**
 * @file
 *
 * Define Sample App Events IDs
 */

#ifndef SAMPLE_APP_EVENTS_H
#define SAMPLE_APP_EVENTS_H

typedef enum
{
    SAMPLE_APP_RESERVED_EID,
    SAMPLE_STARTUP_INF_EID,
    SAMPLE_APP_CC_ERR_EID,
    SAMPLE_APP_NOOP_INF_EID,
    SAMPLE_APP_RESET_INF_EID,
    SAMPLE_APP_MID_ERR_EID,
    SAMPLE_APP_CMD_LEN_ERR_EID,
    SAMPLE_APP_TLM_LEN_ERR_EID,
    SAMPLE_APP_PIPE_ERR_EID,
    SAMPLE_APP_VALUE_INF_EID,
    SAMPLE_APP_CR_PIPE_ERR_EID,
    SAMPLE_APP_SUB_HK_ERR_EID,
    SAMPLE_APP_SUB_CMD_ERR_EID,
    SAMPLE_APP_TABLE_REG_ERR_EID
} SAMPLE_EventID_t;

#endif /* SAMPLE_APP_EVENTS_H */
