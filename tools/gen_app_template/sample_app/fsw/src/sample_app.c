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
#include "sample_utils.h"
#include "sample_app_cmds.h"
#include "sample_app_dispatch.h"
#include "sample_app_tbl.h"

/*
** global data
*/
SAMPLE_GlobalData_t SAMPLE_GlobalData;

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
        SAMPLE_GlobalData.RunStatus = CFE_ES_RunStatus_APP_ERROR;
    }

    /*
    ** Sample App Runloop
    */
    while (CFE_ES_RunLoop(&SAMPLE_GlobalData.RunStatus) == true)
    {
        /*
        ** Performance Log Exit Stamp
        */
        CFE_ES_PerfLogExit(SAMPLE_APP_PERF_ID);

        /* Pend on receipt of command packet */
        status =
            CFE_SB_ReceiveBuffer(&SBBufPtr, SAMPLE_GlobalData.CommandPipe.Id, CFE_SB_PEND_FOREVER);

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

            SAMPLE_GlobalData.RunStatus = CFE_ES_RunStatus_APP_ERROR;
        }
    }

    /*
    ** Performance Log Exit Stamp
    */
    CFE_ES_PerfLogExit(SAMPLE_APP_PERF_ID);

    CFE_ES_ExitApp(SAMPLE_GlobalData.RunStatus);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  */
/*                                                                            */
/* Initialization                                                             */
/*                                                                            */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

CFE_Status_t SAMPLE_AppInit(void)
{
    CFE_Status_t status = CFE_SUCCESS;

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
