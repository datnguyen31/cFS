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

#endif