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
 *   This file contains the source code for the Sample App utility functions
 */

/*
** Include Files:
*/
#include "sample_app.h"
#include "../inc/sample_app_eventids.h"
#include "sample_app_tbl.h"
#include "sample_utils.h"

extern SAMPLE_GlobalData_t SAMPLE_GlobalData;
static CFE_EVS_BinFilter_t SAMPLE_EventFilters[] = {
    /* Event ID    mask */
    {SAMPLE_STARTUP_INF_EID, 0x0000},
};
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/* Verify command packet length                                               */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
bool SAMPLE_APP_VerifyCmdLength(const CFE_MSG_Message_t* MsgPtr, size_t ExpectedLength)
{
    bool              result       = true;
    size_t            ActualLength = 0;
    CFE_SB_MsgId_t    MsgId        = CFE_SB_INVALID_MSG_ID;
    CFE_MSG_FcnCode_t FcnCode      = 0;

    CFE_MSG_GetSize(MsgPtr, &ActualLength);

    /*
    ** Verify the command packet length.
    */
    if (ExpectedLength != ActualLength)
    {
        CFE_MSG_GetMsgId(MsgPtr, &MsgId);
        CFE_MSG_GetFcnCode(MsgPtr, &FcnCode);

        CFE_EVS_SendEvent(SAMPLE_APP_CMD_LEN_ERR_EID,
                          CFE_EVS_EventType_ERROR,
                          "Invalid Msg length: ID = 0x%X,  CC = %u, Len = %u, Expected = %u",
                          (unsigned int)CFE_SB_MsgIdToValue(MsgId),
                          (unsigned int)FcnCode,
                          (unsigned int)ActualLength,
                          (unsigned int)ExpectedLength);

        result = false;

        SAMPLE_GlobalData.CmdRejectedCnt++;
    }

    return result;
}

bool SAMPLE_APP_VerifyTlmLength(const CFE_MSG_Message_t* MsgPtr, size_t ExpectedLength)
{
    bool           result       = true;
    size_t         ActualLength = 0;
    CFE_SB_MsgId_t MsgId        = CFE_SB_INVALID_MSG_ID;

    CFE_MSG_GetSize(MsgPtr, &ActualLength);

    /**
     * Verify the telemetry packet length
     */
    if (ExpectedLength != ActualLength)
    {
        CFE_MSG_GetMsgId(MsgPtr, &MsgId);

        CFE_EVS_SendEvent(SAMPLE_APP_TLM_LEN_ERR_EID,
                          CFE_EVS_EventType_ERROR,
                          "Invalid Msg length: ID = 0x%X, Len = %u, Expected = %u",
                          (unsigned int)CFE_SB_MsgIdToValue(MsgId),
                          (unsigned int)ActualLength,
                          (unsigned int)ExpectedLength);

        result = false;

        SAMPLE_GlobalData.CmdRejectedCnt++;
    }

    return (result);
}

CFE_Status_t SAMPLE_APP_EsInit(void)
{
    return CFE_SUCCESS;
}

CFE_Status_t SAMPLE_APP_EvsInit(void)
{
    CFE_Status_t status = CFE_SUCCESS;

    status = CFE_EVS_Register(SAMPLE_EventFilters, 0, CFE_EVS_EventFilter_BINARY);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("Sample App: Error Registering Events, RC = 0x%08lX\n",
                             (unsigned long)status);
    }

    return status;
}
CFE_Status_t SAMPLE_APP_SbInit(void)
{
    CFE_Status_t status = CFE_SUCCESS;

    /*
    ** Create Software Bus message pipe.
    */
    status = CFE_SB_CreatePipe(&SAMPLE_GlobalData.CommandPipe.Id,
                               SAMPLE_GlobalData.CommandPipe.Depth,
                               SAMPLE_GlobalData.CommandPipe.Name);
    if (status != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(SAMPLE_APP_CR_PIPE_ERR_EID,
                          CFE_EVS_EventType_ERROR,
                          "Error creating SB Command Pipe, RC = 0x%08lX",
                          (unsigned long)status);
    }
    else
    {
        /*
         ** Subscribe to Housekeeping request commands
         */
        status = CFE_SB_Subscribe(CFE_SB_ValueToMsgId(SAMPLE_APP_SCHED_CMD_MID),
                                  SAMPLE_GlobalData.CommandPipe.Id);
        if (status != CFE_SUCCESS)
        {
            CFE_EVS_SendEvent(SAMPLE_APP_SUB_HK_ERR_EID,
                              CFE_EVS_EventType_ERROR,
                              "Error Subscribing to Schedule request, RC = 0x%08lX",
                              (unsigned long)status);
        }

        /*
         ** Subscribe to operating command packets
         */
        status = CFE_SB_Subscribe(CFE_SB_ValueToMsgId(SAMPLE_APP_OPER_CMD_MID),
                                  SAMPLE_GlobalData.CommandPipe.Id);
        if (status != CFE_SUCCESS)
        {
            CFE_EVS_SendEvent(SAMPLE_APP_SUB_CMD_ERR_EID,
                              CFE_EVS_EventType_ERROR,
                              "Sample App: Error Subscribing to Commands, RC = 0x%08lX",
                              (unsigned long)status);
        }
    }

    /*
     ** Initialize telemery
     */
    CFE_MSG_Init(CFE_MSG_PTR(SAMPLE_GlobalData.HkTlm.TelemetryHeader),
                 CFE_SB_ValueToMsgId(SAMPLE_APP_HK_TLM_MID),
                 sizeof(SAMPLE_GlobalData.HkTlm));

    return status;
}

CFE_Status_t SAMPLE_APP_TblInit(void)
{
    return CFE_SUCCESS;
}

CFE_Status_t SAMPLE_APP_TimeInit(void)
{
    return CFE_SUCCESS;
}