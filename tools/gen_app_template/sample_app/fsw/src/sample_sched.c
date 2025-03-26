#include "sample_sched.h"

#include "common_types.h"
#include "sample_app.h"

extern SAMPLE_AppData_t SAMPLE_AppData;

static void SAMPLE_ReportAppHousekeeping(void);

void SAMPLE_ProcessSchedCommand(void)
{
    SAMPLE_AppData.Msg.CommandCode = CFE_SB_GetCmdCode(SAMPLE_AppData.MsgPtr);

    switch (SAMPLE_AppData.Msg.CommandCode)
    {
        case SAMPLE_APPLICATION_HK_CC:
            SAMPLE_ReportAppHousekeeping();
            break;

        case SAMPLE_MISSION_HK_CC:
            // So on
            break;

        default:
            SAMPLE_AppData.CmdRejectedCnt++;
            CFE_EVS_SendEvent(SAMPLE_GENERIC_ERR_EID, CFE_EVS_EventType_ERROR,
                              "SAMPLE: invalid command packet,MID = 0x%x", SAMPLE_AppData.Msg.Id);
            break;
    }
}

static void SAMPLE_ReportAppHousekeeping(void)
{
    if (!SAMPLE_VerifyCmdLength(SAMPLE_AppData.MsgPtr, sizeof(SAMPLE_NoArgsCmd_t)))
    {
        SAMPLE_AppData.CmdRejectedCnt++;
        CFE_EVS_SendEvent(SAMPLE_GENERIC_ERR_EID, CFE_EVS_EventType_ERROR,
                          "SAMPLE: Sending HK error");
        return;
    }

    SAMPLE_HousekeepingTlm_t SAMPLE_HkTelemetryPkt;

    CFE_SB_InitMsg(&SAMPLE_HkTelemetryPkt, SAMPLE_APP_HK_TLM_MID, sizeof(SAMPLE_HousekeepingTlm_t),
                   true);

    SAMPLE_HkTelemetryPkt.CmdAcceptedCnt = SAMPLE_AppData.CmdAcceptedCnt;
    SAMPLE_HkTelemetryPkt.CmdRejectedCnt = SAMPLE_AppData.CmdRejectedCnt;

    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&SAMPLE_HkTelemetryPkt);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&SAMPLE_HkTelemetryPkt);

    CFE_EVS_SendEvent(SAMPLE_GENERIC_INF_EID, CFE_EVS_EventType_INFORMATION,
                      "SAMPLE: Sending HK Msg");

    return;
} /* End of SAMPLE_ProcessSchedCommand() */