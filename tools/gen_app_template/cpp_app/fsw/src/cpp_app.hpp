#ifndef _cpp_app_hpp_
#define _cpp_app_hpp_

extern "C"
{
#include "cfe.h"
}

#include "../mission/cpp_app_events.hpp"
#include "../mission/cpp_app_msg.hpp"
#include "../mission/cpp_app_perfids.hpp"

#include "../platform/cpp_app_platform_cfg.hpp"
#include "../platform/cpp_app_msgids.hpp"
#include "../platform/cpp_app_version.hpp"

namespace CppApp
{

class CppAppData
{
    struct CppApp_PipeAttb_t
    {
        boolean         IsActive;
        CFE_SB_PipeId_t Id;
        uint16          Depth;
        char            Name[OS_MAX_API_NAME];
        int32           Timeout;
    };

    struct CppApp_TblAttb_t
    {
        boolean                   IsActive;
        CFE_TBL_Handle_t          Handle;
        char                      Name[OS_MAX_API_NAME];
        char                      Path[OS_MAX_PATH_LEN];
        uint32                    Size;
        uint16                    TblOpt;
        CFE_TBL_CallbackFuncPtr_t TblValidationFuncPtr;
    };

  public:
    /**
     * @brief ES Attributes
     */
    uint32 RunStatus;
    uint8  CmdAcceptedCnt;
    uint8  CmdRejectedCnt;

    /**
     * @brief EVS Attributes
     */
    CFE_EVS_BinFilter_t EventFilters[CPP_APP_EVENT_NUM];

    /**
     * @brief SB Attributes
     */
    CFE_SB_MsgPtr_t   MsgPtr;
    CppApp_PipeAttb_t CmdPipe;

    CFE_ES_CDSHandle_t CDS;

    CppAppData();

    int32 init();
    void  run();
    void  exit();

  private:
    int32 CPPAPP_ES_Init();
    int32 CPPAPP_EVS_Init();
    int32 CPPAPP_SB_Init();
    int32 CPPAPP_TBL_Init();
    int32 CPPAPP_TIME_Init();
};

} // namespace CppApp
#endif // _cpp_app_hpp_