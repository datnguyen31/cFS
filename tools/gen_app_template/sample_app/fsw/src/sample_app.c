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
** File: sample_app.c
**
** Purpose:
**   This file contains the source code for the Sample App.
**
*******************************************************************************/

/*
**   Include Files:
*/

#include "sample_app.h"
#include "sample_init.h"
#include "sample_gnd.h"

SAMPLE_AppData_t SAMPLE_AppData;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  */
/*                                                                            */
/* SAMPLE_AppInit() --  initialization                                       */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
int32 SAMPLE_AppInit(void)
{
    int32 Status = CFE_SUCCESS;

    Status = SAMPLE_EarlyDataInit();
    if (Status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("SAMPLE: Failed to initialize Sample Data (0x%08X)\n", Status);
        return (Status);
    }

    Status = SAMPLE_ES_DataInit();
    if (Status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("SAMPLE: Failed to initialize ES Data (0x%08X)\n", Status);
        return (Status);
    }

    Status = SAMPLE_EVS_DataInit();
    if (Status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("SAMPLE: Failed to initialize EVS Data (0x%08X)\n", Status);
        return (Status);
    }

    Status = SAMPLE_SB_DataInit();
    if (Status != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(SAMPLE_GENERIC_ERR_EID, CFE_EVS_EventType_ERROR,
                          "SAMPLE App: Error Initializing SB Data,RC=0x%08X", (unsigned int)Status);
        return (Status);
    }

    Status = SAMPLE_TBL_DataInit();
    if (Status != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(SAMPLE_GENERIC_ERR_EID, CFE_EVS_EventType_ERROR,
                          "SAMPLE App: Error Initializing TBL Data,RC=0x%08X",
                          (unsigned int)Status);
        return (Status);
    }

    Status = SAMPLE_TIME_DataInit();
    if (Status != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(SAMPLE_GENERIC_ERR_EID, CFE_EVS_EventType_ERROR,
                          "SAMPLE App: Error Initializing TIME Data,RC=0x%08X",
                          (unsigned int)Status);
        return (Status);
    }

    CFE_EVS_SendEvent(SAMPLE_GENERIC_INF_EID, CFE_EVS_EventType_INFORMATION,
                      "SAMPLE App Initialized. Version %d.%d.%d.%d", SAMPLE_APP_MAJOR_VERSION,
                      SAMPLE_APP_MINOR_VERSION, SAMPLE_APP_REVISION, SAMPLE_APP_MISSION_REV);

    return OS_SUCCESS;
} /* End of SAMPLE_AppInit() */

/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* SAMPLE_AppMain() -- Application entry point and main process loop          */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * *  * * * * **/
void SAMPLE_AppMain(void)
{
    int32 Status;

    CFE_ES_PerfLogEntry(SAMPLE_APP_PERF_ID);

    Status = SAMPLE_AppInit();
    if (Status != CFE_SUCCESS)
    {
        SAMPLE_AppData.RunStatus = CFE_ES_RunStatus_APP_ERROR;
    }

    /*
    ** SAMPLE Runloop
    */
    while (CFE_ES_RunLoop(&SAMPLE_AppData.RunStatus) == true)
    {
        CFE_ES_PerfLogExit(SAMPLE_APP_PERF_ID);

        /* Pend on receipt of command packet -- timeout set to 500 millisecs */
        Status = CFE_SB_RcvMsg(&SAMPLE_AppData.MsgPtr, SAMPLE_AppData.Msg.Pipe.Id,
                               SAMPLE_AppData.Msg.Pipe.Timeout);

        CFE_ES_PerfLogEntry(SAMPLE_APP_PERF_ID);

        if (Status == CFE_SUCCESS)
        {
            SAMPLE_AppData.Msg.Length = CFE_SB_GetTotalMsgLength(SAMPLE_AppData.MsgPtr);
            SAMPLE_ProcessCmdMsg();
        }
    }

    CFE_ES_ExitApp(SAMPLE_AppData.RunStatus);

} /* End of SAMPLE_AppMain() */

void SAMPLE_ProcessCmdMsg(void)
{
    SAMPLE_AppData.Msg.Id = CFE_SB_GetMsgId(SAMPLE_AppData.MsgPtr);

    switch (SAMPLE_AppData.Msg.Id)
    {
        case SAMPLE_APP_GND_CMD_MID:
            SAMPLE_ProcessGroundCommand();
            break;

        case SAMPLE_APP_SCHED_CMD_MID:
            SAMPLE_ProcessSchedCommand();
            break;

        default:
            SAMPLE_AppData.CmdRejectedCnt++;
            CFE_EVS_SendEvent(SAMPLE_GENERIC_ERR_EID, CFE_EVS_EventType_ERROR,
                              "SAMPLE: invalid command packet,MID = 0x%x",
                              SAMPLE_AppData.Msg.Id);
            break;
    }

    return;
}

bool SAMPLE_VerifyCmdLength(CFE_SB_MsgPtr_t msg, uint16 ExpectedLength)
{
    bool result = true;

    /*
    ** Verify the command packet length.
    */
    if (ExpectedLength != SAMPLE_AppData.Msg.Length)
    {
        CFE_SB_MsgId_t MessageID   = CFE_SB_GetMsgId(msg);
        uint16         CommandCode = CFE_SB_GetCmdCode(msg);

        CFE_EVS_SendEvent(SAMPLE_LEN_ERR_EID, CFE_EVS_EventType_ERROR,
                          "Invalid msg length: ID = 0x%X,  CC = %d, Len = %d, Expected = %d",
                          MessageID, CommandCode, SAMPLE_AppData.Msg.Length, ExpectedLength);
        result = false;
        SAMPLE_AppData.CmdAcceptedCnt++;
    }

    return (result);

} /* End of SAMPLE_VerifyCmdLength() */