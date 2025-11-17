#ifndef SAMPLE_APP_FACILITY_H
#define SAMPLE_APP_FACILITY_H

#include "cfe.h"

typedef struct
{
    uint8           State;
    CFE_SB_PipeId_t Id;
    uint16          Depth;
    char            Name[OS_MAX_API_NAME];
    int32           Timeout;
} SAMPLE_PipeAttb_t;

typedef struct
{
    bool                      State;
    CFE_TBL_Handle_t          Handle;
    char                      Name[OS_MAX_API_NAME];
    char                      Path[OS_MAX_PATH_LEN];
    uint32                    Size;
    uint16                    TblOpt;
    CFE_TBL_CallbackFuncPtr_t ValidateFunc;
} SAMPLE_TblAttb_t;

#endif