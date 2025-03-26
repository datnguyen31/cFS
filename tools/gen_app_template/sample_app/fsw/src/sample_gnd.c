#include "sample_app.h"
#include "sample_gnd.h"

extern SAMPLE_AppData_t SAMPLE_AppData;

static void SAMPLE_ProcessGroundCommand(void);
static void SAMPLE_NoOperation(void);
static void SAMPLE_ResetCounters(void);

static void SAMPLE_ProcessGroundCommand(void)
{
    SAMPLE_AppData.Msg.CommandCode = CFE_SB_GetCmdCode(SAMPLE_AppData.MsgPtr);

    /* Process "known" SAMPLE app ground commands */
    switch (SAMPLE_AppData.Msg.CommandCode)
    {
        case SAMPLE_APP_NOOP_CC:
            SAMPLE_NoOperation();
            break;

        case SAMPLE_APP_RESET_COUNTERS_CC:
            SAMPLE_ResetCounters();
            break;

        default:
            SAMPLE_AppData.CmdRejectedCnt++;
            CFE_EVS_SendEvent(SAMPLE_GENERIC_ERR_EID, CFE_EVS_EventType_ERROR,
                              "SAMPLE: invalid command code,code = %d",
                              SAMPLE_AppData.Msg.CommandCode);
            break;
    }
    return;

} /* End of SAMPLE_ProcessGroundCommand() */

static void SAMPLE_NoOperation(void)
{
    if (!SAMPLE_VerifyCmdLength(SAMPLE_AppData.MsgPtr, SAMPLE_NO_ARGS_CMD_LNGTH))
    {
        SAMPLE_AppData.CmdRejectedCnt++;
        CFE_EVS_SendEvent(SAMPLE_GENERIC_ERR_EID, CFE_EVS_EventType_ERROR,
                          "SAMPLE: Active NOOP error");
        return;
    }

    SAMPLE_AppData.CmdAcceptedCnt++;
    CFE_EVS_SendEvent(SAMPLE_GENERIC_INF_EID, CFE_EVS_EventType_INFORMATION,
                      "SAMPLE: Active NOOP command");
    return;
}

static void SAMPLE_ResetCounters(void)
{
    if (!SAMPLE_VerifyCmdLength(SAMPLE_AppData.MsgPtr, SAMPLE_NO_ARGS_CMD_LNGTH))
    {
        SAMPLE_AppData.CmdRejectedCnt++;
        CFE_EVS_SendEvent(SAMPLE_GENERIC_ERR_EID, CFE_EVS_EventType_ERROR,
                          "SAMPLE: Active RESET error");
        return;
    }

    /* Status of commands processed by the SAMPLE App */
    SAMPLE_AppData.CmdAcceptedCnt = 0;
    SAMPLE_AppData.CmdRejectedCnt = 0;

    CFE_EVS_SendEvent(SAMPLE_GENERIC_INF_EID, CFE_EVS_EventType_INFORMATION,
                      "SAMPLE: Active RESET command");
    return;

} /* End of SAMPLE_ResetCounters() */