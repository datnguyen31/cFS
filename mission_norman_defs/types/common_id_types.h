#ifndef _common_id_types_h_
#define _common_id_types_h_

#include "cfe.h"

// TODO Change MPLAN to COMMON

typedef struct
{
    uint8 ID;
} COMMON_IDU8_t;

typedef struct
{
    uint16 ID;
} COMMON_IDU16_t;

typedef struct
{
    uint32 ID;
} COMMON_IDU32_t;

typedef struct
{
    uint64 ID;
} COMMON_IDU64_t;

typedef struct
{
    int8 ID;
} COMMON_IDI8_t;

typedef struct
{
    int16 ID;
} COMMON_IDI16_t;

typedef struct
{
    int32 ID;
} COMMON_IDI32_t;

typedef struct
{
    int64 ID;
} COMMON_IDI64_t;

#endif