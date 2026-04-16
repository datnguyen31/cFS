#ifndef _common_cfe_types_h_
#define _common_cfe_types_h_

#include "cfe.h"

typedef struct
{
    uint8           State;
    CFE_SB_PipeId_t ID;
    uint16          Depth;
    int32           Timeout;
} NOMAD_PipeAttb_t;

typedef struct
{
    uint8            State;
    uint8            Loaded;
    CFE_TBL_Handle_t Handle;
} NOMAD_TblAttb_t;

#endif