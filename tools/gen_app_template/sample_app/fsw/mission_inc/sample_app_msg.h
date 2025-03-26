/*******************************************************************************
**
**      GSC-18128-1, "Core Flight Executive Version 6.7"
**
**      Copyright (c) 2006-2019 United States Government as represented by
**      the Administrator of the National Aeronautics and Space Administration.
**      All Rights Reserved.
**
**      Licensed under the Apache License, Version 2.0 (the "License");
**      you may not use this file except in compliance with the License.
**      You may obtain a copy of the License at
**
**        http://www.apache.org/licenses/LICENSE-2.0
**
**      Unless required by applicable law or agreed to in writing, software
**      distributed under the License is distributed on an "AS IS" BASIS,
**      WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
**      See the License for the specific language governing permissions and
**      limitations under the License.
**
** File: sample_app_msg.h
**
** Purpose:
**  Define SAMPLE App  Messages and info
**
** Notes:
**
**
*******************************************************************************/
#ifndef _sample_app_msg_h_
#define _sample_app_msg_h_

#include "common_types.h"

/*
** SAMPLE App command codes
*/

typedef enum
{
    SAMPLE_APP_NOOP_CC,
    SAMPLE_APP_RESET_COUNTERS_CC
} SAMPLE_GroundCommandCode_t;

typedef enum
{
    SAMPLE_APPLICATION_HK_CC,
    SAMPLE_MISSION_HK_CC
} SAMPLE_HousekeepingCommandCode_t;

/*************************************************************************/
/*
** Type definition (generic "no arguments" command)
*/
typedef struct
{
    uint8 CmdHeader[CFE_SB_CMD_HDR_SIZE];
} SAMPLE_NoArgsCmd_t;
#define SAMPLE_NO_ARGS_CMD_LNGTH sizeof(SAMPLE_NoArgsCmd_t)

/*************************************************************************/
/*
** Type definition (SAMPLE App housekeeping)
*/
typedef struct
{
    uint8 TlmHeader[CFE_SB_TLM_HDR_SIZE];
    uint8 CmdAcceptedCnt;
    uint8 CmdRejectedCnt;
} SAMPLE_HousekeepingTlm_t;
#define SAMPLE_APP_HK_TLM_LNGTH sizeof(SAMPLE_HousekeepingTlm_t)

#endif /* _sample_app_msg_h_ */

/************************/
/*  End of File Comment */
/************************/
