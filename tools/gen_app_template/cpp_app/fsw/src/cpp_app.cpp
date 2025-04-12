#include <iostream>

#include "cpp_app.hpp"

namespace CppApp
{
CppAppData::CppAppData()
{
    RunStatus      = 0;
    CmdAcceptedCnt = 0;
    CmdRejectedCnt = 0;

    CmdPipe.IsActive = false;
    CmdPipe.Id       = 0;
    CmdPipe.Depth    = CPP_APP_PIPE_DEPTH;
    CmdPipe.Timeout  = CPP_APP_PIPE_TIMEOUT;
    CFE_PSP_MemCpy(CmdPipe.Name, CPP_APP_CMD_PIPE_NAME, OS_MAX_API_NAME);
}

int32 CppAppData::CPPAPP_ES_Init()
{
    int32 Status = CFE_SUCCESS;

    Status = CFE_ES_RegisterApp();
    if (Status != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(CPP_APP_ES_ERR_EID, CFE_EVS_EventType_ERROR, "Failed to register the app, RC=0x%08X", Status);
    }

    return (Status);
}

int32 CppAppData::CPPAPP_EVS_Init()
{
    int32 Status = CFE_SUCCESS;

    Status =
        CFE_EVS_Register(EventFilters, sizeof(EventFilters) / sizeof(CFE_EVS_BinFilter_t), CFE_EVS_EventFilter_BINARY);
    if (Status != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(CPP_APP_EVS_ERR_EID, CFE_EVS_EventType_ERROR, "Failed to register events (0x%08X)", Status);
    }

    return (Status);
}

int32 CppAppData::CPPAPP_SB_Init()
{
    int32 Status = CFE_SUCCESS;

    Status = CFE_SB_CreatePipe(&CmdPipe.Id, CmdPipe.Depth, CmdPipe.Name);
    if (Status != CFE_SUCCESS)
    {
        CFE_EVS_SendEvent(CPP_APP_SB_ERR_EID, CFE_EVS_EventType_ERROR, "Failed to create pipe (0x%08X)", Status);
    }

    return (Status);
}

int32 CppAppData::CPPAPP_TBL_Init()
{
    int32 Status = CFE_SUCCESS;

    return (Status);
}

int32 CppAppData::CPPAPP_TIME_Init()
{
    int32 Status = CFE_SUCCESS;

    return (Status);
}

int32 CppAppData::init()
{
    int32 Status = CFE_SUCCESS;

    Status = CPPAPP_ES_Init();
    if (Status != CFE_SUCCESS)
    {
        return (Status);
    }

    Status = CPPAPP_EVS_Init();
    if (Status != CFE_SUCCESS)
    {
        return (Status);
    }

    Status = CPPAPP_SB_Init();
    if (Status != CFE_SUCCESS)
    {
        return (Status);
    }

    Status = CPPAPP_TBL_Init();
    if (Status != CFE_SUCCESS)
    {
        return (Status);
    }

    Status = CPPAPP_TIME_Init();
    if (Status != CFE_SUCCESS)
    {
        return (Status);
    }

    RunStatus = CFE_ES_RunStatus_APP_RUN;

    return (Status);
}

void CppAppData::exit()
{
    CFE_ES_ExitApp(RunStatus);
}

void CppAppData::run()
{
    int32 Status = CFE_SUCCESS;

    while (CFE_ES_RunLoop(&RunStatus) == true)
    {
        CFE_ES_PerfLogExit(CPP_APP_PERF_ID);

        Status = CFE_SB_RcvMsg(&MsgPtr, CmdPipe.Id, CmdPipe.Timeout);

        CFE_ES_PerfLogEntry(CPP_APP_PERF_ID);

        if (Status == CFE_SUCCESS)
        {
            // Process command packet
        }

        std::cout << "CppAppData::run()" << std::endl;
    }
}

} // namespace CppApp

extern "C"
{
    void CppAppEntry()
    {
        int32              Status;
        CppApp::CppAppData CppAppData;

        Status = CppAppData.init();
        if (Status == CFE_SUCCESS)
        {
            CppAppData.run();
        }

        CppAppData.exit();

        return;
    }
}