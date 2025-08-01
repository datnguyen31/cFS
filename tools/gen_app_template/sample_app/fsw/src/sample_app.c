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
#include "sample_app_cmds.h"
#include "sample_app_utils.h"
#include "../inc/sample_app_eventids.h"
#include "sample_app_dispatch.h"
#include "sample_app_tbl.h"
#include "sample_app_version.h"

/*
** global data
*/
SAMPLE_AppData_t SAMPLE_AppData;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * *  * * * * **/
/*                                                                            */
/* Application entry point and main process loop                              */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  * *  * * * * **/
void SAMPLE_AppMain(void)
{
    CFE_Status_t     status;
    CFE_SB_Buffer_t* SBBufPtr;

    /*
    ** Create the first Performance Log entry
    */
    CFE_ES_PerfLogEntry(SAMPLE_APP_PERF_ID);

    /*
    ** Perform application-specific initialization
    ** If the Initialization fails, set the RunStatus to
    ** CFE_ES_RunStatus_APP_ERROR and the App will not enter the RunLoop
    */
    status = SAMPLE_AppInit();
    if (status != CFE_SUCCESS)
    {
        SAMPLE_AppData.RunStatus = CFE_ES_RunStatus_APP_ERROR;
    }

    /*
    ** Sample App Runloop
    */
    while (CFE_ES_RunLoop(&SAMPLE_AppData.RunStatus) == true)
    {
        /*
        ** Performance Log Exit Stamp
        */
        CFE_ES_PerfLogExit(SAMPLE_APP_PERF_ID);

        /* Pend on receipt of command packet */
        status =
            CFE_SB_ReceiveBuffer(&SBBufPtr, SAMPLE_AppData.CommandPipe.Id, CFE_SB_PEND_FOREVER);

        /*
        ** Performance Log Entry Stamp
        */
        CFE_ES_PerfLogEntry(SAMPLE_APP_PERF_ID);

        if (status == CFE_SUCCESS)
        {
            SAMPLE_APP_TaskPipe(SBBufPtr);
        }
        else
        {
            CFE_EVS_SendEvent(SAMPLE_APP_PIPE_ERR_EID,
                              CFE_EVS_EventType_ERROR,
                              "SAMPLE APP: SB Pipe Read Error, App Will Exit");

            SAMPLE_AppData.RunStatus = CFE_ES_RunStatus_APP_ERROR;
        }
    }

    /*
    ** Performance Log Exit Stamp
    */
    CFE_ES_PerfLogExit(SAMPLE_APP_PERF_ID);

    CFE_ES_ExitApp(SAMPLE_AppData.RunStatus);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  */
/*                                                                            */
/* Initialization                                                             */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

static CFE_Status_t SAMPLE_APP_EsInit(void)
{
    return CFE_SUCCESS;
}

static CFE_Status_t SAMPLE_APP_EvsInit(void)
{
    CFE_Status_t status = CFE_SUCCESS;

    status = CFE_EVS_Register(NULL, 0, CFE_EVS_EventFilter_BINARY);
    if (status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("Sample App: Error Registering Events, RC = 0x%08lX\n",
                             (unsigned long)status);
    }

    return status;
}
static CFE_Status_t SAMPLE_APP_SbInit(void)
{
    CFE_Status_t status = CFE_SUCCESS;

    /*
    ** Create Software Bus message pipe.
    */
    status = CFE_SB_CreatePipe(&SAMPLE_AppData.CommandPipe.Id,
                               SAMPLE_AppData.CommandPipe.Depth,
                               SAMPLE_AppData.CommandPipe.Name);
    if (status != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(SAMPLE_APP_CR_PIPE_ERR_EID,
                          CFE_EVS_EventType_ERROR,
                          "Sample App: Error creating SB Command Pipe, RC = 0x%08lX",
                          (unsigned long)status);
    }
    else
    {
        /*
         ** Subscribe to Housekeeping request commands
         */
        status = CFE_SB_Subscribe(CFE_SB_ValueToMsgId(SAMPLE_APP_SCHED_CMD_MID),
                                  SAMPLE_AppData.CommandPipe.Id);
        if (status != CFE_SUCCESS)
        {
            CFE_EVS_SendEvent(SAMPLE_APP_SUB_HK_ERR_EID,
                              CFE_EVS_EventType_ERROR,
                              "Sample App: Error Subscribing to Schedule request, RC = 0x%08lX",
                              (unsigned long)status);
        }

        /*
         ** Subscribe to ground command packets
         */
        status = CFE_SB_Subscribe(CFE_SB_ValueToMsgId(SAMPLE_APP_GND_CMD_MID),
                                  SAMPLE_AppData.CommandPipe.Id);
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
    CFE_MSG_Init(CFE_MSG_PTR(SAMPLE_AppData.HkTlm.TelemetryHeader),
                 CFE_SB_ValueToMsgId(SAMPLE_APP_HK_TLM_MID),
                 sizeof(SAMPLE_AppData.HkTlm));

    return status;
}

static CFE_Status_t SAMPLE_APP_TblInit(void)
{
    return CFE_SUCCESS;
}

CFE_Status_t SAMPLE_APP_TimeInit(void)
{
    return CFE_SUCCESS;
}

CFE_Status_t SAMPLE_AppInit(void)
{
    CFE_Status_t status = CFE_SUCCESS;

    /* Zero out the global data structure */
    memset(&SAMPLE_AppData, 0, sizeof(SAMPLE_AppData));

    SAMPLE_AppData.RunStatus = CFE_ES_RunStatus_APP_RUN;

    /*
    ** Initialize app configuration data
    */
    SAMPLE_AppData.CommandPipe.Depth = SAMPLE_APP_CMD_PIPE_DEPTH;

    strncpy(SAMPLE_AppData.CommandPipe.Name,
            "SAMPLE_APP_CMD_PIPE",
            sizeof(SAMPLE_AppData.CommandPipe.Name));
    SAMPLE_AppData.CommandPipe.Name[sizeof(SAMPLE_AppData.CommandPipe.Name) - 1] = 0;
    SAMPLE_AppData.CommandPipe.Timeout = SAMPLE_APP_CMD_PIPE_TIMEOUT;

    status = SAMPLE_APP_EvsInit();
    if (status != CFE_SUCCESS)
    {
        return status;
    }

    status = SAMPLE_APP_EsInit();
    if (status != CFE_SUCCESS)
    {
        return status;
    }

    status = SAMPLE_APP_SbInit();
    if (status != CFE_SUCCESS)
    {
        return status;
    }

    status = SAMPLE_APP_TblInit();
    if (status != CFE_SUCCESS)
    {
        return status;
    }

    status = SAMPLE_APP_TimeInit();
    if (status != CFE_SUCCESS)
    {
        return status;
    }

    if (status == CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(SAMPLE_STARTUP_INF_EID,
                          CFE_EVS_EventType_INFORMATION,
                          "Sample App Initialized. Version %s",
                          SAMPLE_APP_LAST_OFFICIAL);
    }
    return status;
}
