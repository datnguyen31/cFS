#ifndef _mission_nomad_modedefs_h_
#define _mission_nomad_modedefs_h_

#include "cfe.h"

#define NOMAD_INVALID_VALUE 0xFFFFFFFF

/**
 * @brief Target description
 *
 * @param TARGET_CARTESIAN Cartesian coordinate
 * @param TARGET_LLA LLA coordinate
 * @param TARGET_RPY Roll, Pitch and Yaw
 * @param TARGET_QUATERNION Quaternion
 *
 */
typedef enum
{
    TARGET_INVALID = NOMAD_INVALID_VALUE,
    TARGET_ETHER   = 0,
    TARGET_CARTESIAN,
    TARGET_LLA,
    TARGET_RPY,
    TARGET_QUATERNION,
    TARGET_MAX
} NOMAD_TargetList_t;
#define TARGET_NUM TARGET_MAX

typedef struct
{
    float  Value[4];
    uint32 Type;
} NOMAD_TargetFourValue_t;

/**
 * @brief Mode description
 *
 */
typedef enum
{
    MODE_INVALID = NOMAD_INVALID_VALUE,
    MODE_STANDBY = 0,
    MODE_TRAVERSE,
    MODE_SCIENCE,
    MODE_MAX
} NOMAD_ModeList_t;
#define MODE_NUM MODE_MAX

/**
 * @brief Standby mode's plan list description
 *
 * @param STANDBY_PLAN_A Hibernation
 * @param STANDBY_PLAN_B Idle
 *
 */
typedef enum
{
    STANDBY_PLAN_INVALID = NOMAD_INVALID_VALUE,
    STANDBY_PLAN_A       = 0,
    STANDBY_PLAN_B,
    STANDBY_PLAN_MAX
} NOMAD_StandbyPlanList_t;
#define STANDBY_PLAN_NUM STANDBY_PLAN_MAX

/**
 * @brief Traverse mode's plan list description
 *
 * @param TRAVERSE_PLAN_A Traverse Manual Control
 * @param TRAVERSE_PLAN_B Blind Drive
 * @param TRAVERSE_PLAN_C Blind Goto Waypoint
 * @param TRAVERSE_PLAN_D Autonomous Navigation
 *
 */
typedef enum
{
    TRAVERSE_PLAN_INVALID = NOMAD_INVALID_VALUE,
    TRAVERSE_PLAN_A       = 0,
    TRAVERSE_PLAN_B,
    TRAVERSE_PLAN_C,
    TRAVERSE_PLAN_D,
    TRAVERSE_PLAN_MAX
} NOMAD_TraversePlanList_t;
#define TRAVERSE_PLAN_NUM TRAVERSE_PLAN_MAX

/**
 * @brief Science mode's plan list description
 *
 * @param SCIENCE_PLAN_A Take a picture
 * @param SCIENCE_PLAN_B Arm manual control
 * @param SCIENCE_PLAN_C Arm trajectorized control
 * @param SCIENCE_PLAN_D Drilling
 *
 */
typedef enum
{
    SCIENCE_PLAN_INVALID = NOMAD_INVALID_VALUE,
    SCIENCE_PLAN_A       = 0,
    SCIENCE_PLAN_B,
    SCIENCE_PLAN_C,
    SCIENCE_PLAN_D,
    SCIENCE_PLAN_MAX
} NOMAD_SciencePlanList_t;
#define SCIENCE_PLAN_NUM SCIENCE_PLAN_MAX

#define NOMAD_PLAN_NUM (STANDBY_PLAN_NUM + TRAVERSE_PLAN_NUM + SCIENCE_PLAN_NUM)

/**
 * @brief Side plan list description
 *
 * @param SIDE_PLAN_A Standup mechanism
 * @param SIDE_PLAN_B Regular synchronization
 * @param SIDE_PLAN_C Power charging
 * @param SIDE_PLAN_D Start downlink
 * @param SIDE_PLAN_E Start uplink
 * @param SIDE_PLAN_F Send SOS signal
 * @param SIDE_PLAN_G Regular diagnostic sequence
 *
 */
typedef enum
{
    SIDE_PLAN_INVALID = NOMAD_INVALID_VALUE,
    SIDE_PLAN_A       = 0,
    SIDE_PLAN_B,
    SIDE_PLAN_C,
    SIDE_PLAN_D,
    SIDE_PLAN_E,
    SIDE_PLAN_F,
    SIDE_PLAN_G,
    SIDE_PLAN_MAX
} NOMAD_SidePlanList_t;
#define SIDE_PLAN_NUM SIDE_PLAN_MAX

#define SIDE_PLAN_A_NAME "Standup Mechanism"
#define SIDE_PLAN_B_NAME "Regular Synchronization"
#define SIDE_PLAN_C_NAME "Power charging"
#define SIDE_PLAN_D_NAME "Start downlink"
#define SIDE_PLAN_E_NAME "Start uplink"
#define SIDE_PLAN_F_NAME "Send SOS signal"
#define SIDE_PLAN_G_NAME "Regular diagnostic sequence"

#if (SIDE_PLAN_NUM > 65535)
#error "SIDE_PLAN_NUM exceeds uint16 limit"
#endif

#endif