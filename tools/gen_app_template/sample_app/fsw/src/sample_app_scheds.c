#include "sample_app.h"
#include "sample_app_scheds.h"
#include "sample_app_msgids.h"
#include "../inc/sample_app_eventids.h"
#include "sample_app_version.h"
#include "sample_app_tbl.h"
#include "sample_utils.h"
#include "sample_app_msg.h"

extern SAMPLE_GlobalData_t SAMPLE_GlobalData;

static CFE_Status_t SAMPLE_APP_SendHkCmd(const SAMPLE_APP_SchedCmd_t* Msg);

void SAMPLE_APP_ProcessSchedCommand(const CFE_SB_Buffer_t* SBBufPtr)
{
    CFE_MSG_FcnCode_t CommandCode = 0;

    CFE_MSG_GetFcnCode(&SBBufPtr->Msg, &CommandCode);

    switch (CommandCode)
    {
        case SAMPLE_APP_INTERNAL_HK_CC:
            if (SAMPLE_APP_VerifyCmdLength(&SBBufPtr->Msg, sizeof(SAMPLE_APP_SchedCmd_t)))
            {
                SAMPLE_APP_SendHkCmd((const SAMPLE_APP_SchedCmd_t*)SBBufPtr);
            }
            break;

        default:
            CFE_EVS_SendEvent(SAMPLE_APP_CC_ERR_EID,
                              CFE_EVS_EventType_ERROR,
                              "Invalid scheduled command code: CC = %d",
                              CommandCode);
            break;
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
/*                                                                            */
/*  Purpose:                                                                  */
/*         This function is triggered in response to a task telemetry request */
/*         from the housekeeping task. This function will gather the Apps     */
/*         telemetry, packetize it and send it to the housekeeping task via   */
/*         the software bus                                                   */
/* * * * * * * * * * * * * * * * * * * * * * * *  * * * * * * *  * *  * * * * */
CFE_Status_t SAMPLE_APP_SendHkCmd(const SAMPLE_APP_SchedCmd_t* Msg)
{
    SAMPLE_APP_HkTlm_t HkTlm;

    /*
     ** Initialize telemery
     */
    CFE_MSG_Init(CFE_MSG_PTR(HkTlm.TelemetryHeader),
                 CFE_SB_ValueToMsgId(SAMPLE_APP_HK_TLM_MID),
                 sizeof(HkTlm));
    /*
    ** Get command execution counters...
    */
    HkTlm.Payload.CmdRejectedCnt = SAMPLE_GlobalData.CmdRejectedCnt;
    HkTlm.Payload.CmdAcceptedCnt = SAMPLE_GlobalData.CmdAcceptedCnt;

    /*
    ** Send housekeeping telemetry packet...
    */
    CFE_SB_TimeStampMsg(CFE_MSG_PTR(HkTlm.TelemetryHeader));
    CFE_SB_TransmitMsg(CFE_MSG_PTR(HkTlm.TelemetryHeader), true);

    return CFE_SUCCESS;
}