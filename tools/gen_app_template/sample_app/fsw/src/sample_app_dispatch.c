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
 * \file
 *   This file contains the source code for the Sample App.
 */

/*
** Include Files:
*/
#include "sample_app.h"
#include "sample_app_dispatch.h"
#include "sample_app_cmds.h"
#include "sample_app_scheds.h"
#include "../inc/sample_app_eventids.h"
#include "sample_app_msgids.h"
#include "sample_app_msg.h"

extern SAMPLE_AppData_t SAMPLE_AppData;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/*  Purpose:                                                                  */
/*     This routine will process any packet that is received on the SAMPLE    */
/*     command pipe.                                                          */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
void SAMPLE_APP_TaskPipe(const CFE_SB_Buffer_t* SBBufPtr)
{
    CFE_SB_MsgId_t MsgId = CFE_SB_INVALID_MSG_ID;

    CFE_MSG_GetMsgId(&SBBufPtr->Msg, &MsgId);

    switch (CFE_SB_MsgIdToValue(MsgId))
    {
        case SAMPLE_APP_OPR_CMD_MID:
            SAMPLE_APP_ProcessOperCommand(SBBufPtr);
            break;

        case SAMPLE_APP_SCHED_CMD_MID:
            SAMPLE_APP_ProcessSchedCommand(SBBufPtr);
            break;

        default:
            CFE_EVS_SendEvent(SAMPLE_APP_MID_ERR_EID,
                              CFE_EVS_EventType_ERROR,
                              "SAMPLE: invalid command packet,MID = 0x%x",
                              (unsigned int)CFE_SB_MsgIdToValue(MsgId));
            break;
    }
}
