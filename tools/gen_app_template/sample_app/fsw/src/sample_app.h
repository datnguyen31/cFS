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
** File: sample_app.h
**
** Purpose:
**   This file is main hdr file for the SAMPLE application.
**
**
*******************************************************************************/

#ifndef _sample_app_h_
#define _sample_app_h_

/*
** Required header files.
*/
#include "cfe.h"
#include "cfe_error.h"
#include "cfe_evs.h"
#include "cfe_sb.h"
#include "cfe_es.h"

#include <string.h>
#include <errno.h>
#include <unistd.h>

#include "sample_app_perfids.h"
#include "sample_app_msgids.h"
#include "sample_app_msg.h"
#include "sample_app_events.h"
#include "sample_app_version.h"

/***********************************************************************/

#define SAMPLE_SUCCESS CFE_SUCCESS
#define SAMPLE_ERROR   CFE_OS_ERROR

#define SAMPLE_STATE_DISABLE 0
#define SAMPLE_STATE_ENABLE  1

#define SAMPLE_PIPE_DEPTH   32
#define SAMPLE_PIPE_TIMEOUT 500
/************************************************************************
** Type Definitions
*************************************************************************/

/**
 * @brief This is an example data structure, delete it if you don't need it
 */
typedef struct
{
    boolean         Active;
    CFE_SB_PipeId_t Id;
    uint16          Depth;
    char            Name[OS_MAX_API_NAME];
    int32           Timeout;
} SAMPLE_PipeAttb_t;

/**
 * @brief This is an example data structure, delete it if you don't need it
 */
typedef struct
{
    CFE_SB_MsgId_t    Id;
    uint16            CommandCode;
    uint16            Length;
    SAMPLE_PipeAttb_t Pipe;
} SAMPLE_MsgAttb_t;

/**
 * @brief This is an example data structure, delete it if you don't need it
 */
typedef struct
{
    boolean                   Active;
    CFE_TBL_Handle_t          Handle;
    char                      Name[OS_MAX_API_NAME];
    char                      Path[OS_MAX_PATH_LEN];
    uint32                    Size;
    uint16                    TblOpt;
    CFE_TBL_CallbackFuncPtr_t TblValidationFuncPtr;
} SAMPLE_TblAttb_t;

typedef struct
{
    uint32 RunStatus;

    uint8 CmdAcceptedCnt;
    uint8 CmdRejectedCnt;

    CFE_SB_MsgPtr_t   MsgPtr;
    SAMPLE_PipeAttb_t CmdPipe;
    SAMPLE_MsgAttb_t  Msg;

    CFE_ES_CDSHandle_t CDS;
} SAMPLE_AppData_t;

bool SAMPLE_VerifyCmdLength(CFE_SB_MsgPtr_t msg, uint16 ExpectedLength);
void SAMPLE_ProcessCmdMsg(void);

#endif /* _sample_app_h_ */
