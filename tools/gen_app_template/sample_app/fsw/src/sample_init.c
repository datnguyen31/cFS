#include "sample_init.h"
#include "sample_app.h"
#include "sample_app_events.h"

extern SAMPLE_AppData_t    SAMPLE_AppData;
static CFE_EVS_BinFilter_t SAMPLE_EventFilters[] = {
    /* Event ID    mask */
    {SAMPLE_GENERIC_INF_EID, 0x0000},
    {SAMPLE_GENERIC_ERR_EID, 0x0000},
};

int32 SAMPLE_EarlyDataInit(void)
{
    CFE_PSP_MemSet(&SAMPLE_AppData, 0, sizeof(SAMPLE_AppData));

    SAMPLE_AppData.CmdAcceptedCnt = 0;
    SAMPLE_AppData.CmdRejectedCnt = 0;

    /**
     * Setup pipe information
     */
    SAMPLE_AppData.Msg.Pipe.Active  = SAMPLE_STATE_DISABLE;
    SAMPLE_AppData.Msg.Pipe.Id      = 0;
    SAMPLE_AppData.Msg.Pipe.Depth   = SAMPLE_PIPE_DEPTH;
    SAMPLE_AppData.Msg.Pipe.Timeout = SAMPLE_PIPE_TIMEOUT;
    strncpy(SAMPLE_AppData.Msg.Pipe.Name, "SAMPLE_CMD_PIPE", OS_MAX_API_NAME - 1);
    SAMPLE_AppData.Msg.Pipe.Name[OS_MAX_API_NAME - 1] = 0;

    /**
     * Setup table information
     */

    SAMPLE_AppData.RunStatus = CFE_ES_RunStatus_APP_RUN;

    return SAMPLE_SUCCESS;
}

int32 SAMPLE_ES_DataInit(void)
{
    int32 Status = CFE_SUCCESS;

    Status = CFE_ES_RegisterApp();
    if (Status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("SAMPLE: Failed to register the app (0x%08X)\n", Status);
    }

    return (Status);
}

int32 SAMPLE_EVS_DataInit(void)
{
    int32 Status = CFE_SUCCESS;

    /*
     ** Register the events
     */
    Status = CFE_EVS_Register(SAMPLE_EventFilters,
                              sizeof(SAMPLE_EventFilters) / sizeof(CFE_EVS_BinFilter_t),
                              CFE_EVS_EventFilter_BINARY);
    if (Status != CFE_SUCCESS)
    {
        CFE_ES_WriteToSysLog("SAMPLE: Failed to register events (0x%08X)\n", Status);
    }

    return (Status);
}

int32 SAMPLE_SB_DataInit(void)
{
    int32 Status = CFE_SUCCESS;

    Status = CFE_SB_CreatePipe(&SAMPLE_AppData.Msg.Pipe.Id, SAMPLE_AppData.Msg.Pipe.Depth,
                               SAMPLE_AppData.Msg.Pipe.Name);
    if (Status == CFE_SUCCESS)
    {
        Status = CFE_SB_Subscribe(SAMPLE_APP_GND_CMD_MID, SAMPLE_AppData.Msg.Pipe.Id);
        if (Status != CFE_SUCCESS)
        {
            CFE_EVS_SendEvent(SAMPLE_GENERIC_ERR_EID, CFE_EVS_EventType_ERROR,
                              "Failed to subscribe to SAMPLE_CMD_MID(0x%08X)", Status);
        }

        Status = CFE_SB_Subscribe(SAMPLE_APP_SCHED_CMD_MID, SAMPLE_AppData.Msg.Pipe.Id);
        if (Status != CFE_SUCCESS)
        {
            CFE_EVS_SendEvent(SAMPLE_GENERIC_ERR_EID, CFE_EVS_EventType_ERROR,
                              "Failed to subscribe to SAMPLE_SEND_HK_MID(0x%08X)", Status);
        }
    }
    else
    {
        CFE_EVS_SendEvent(SAMPLE_GENERIC_ERR_EID, CFE_EVS_EventType_ERROR,
                          "Failed to create pipe, RC=0x%08X", Status);
    }

    return (Status);
}

int32 SAMPLE_TBL_DataInit(void)
{
    int32 Status = CFE_SUCCESS;

    return (Status);
}

int32 SAMPLE_TIME_DataInit(void)
{
    int32 Status = CFE_SUCCESS;

    return (Status);
}