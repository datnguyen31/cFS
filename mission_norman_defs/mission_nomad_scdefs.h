#ifndef _mission_nomad_scdefs_h_
#define _mission_nomad_scdefs_h_

#define NOMAD_RTS_CODE_BLOCK(idx) ((unsigned long)(idx) * 10UL)

typedef enum
{
    /**
     * @section A: Nominal actions, start at 0
     * We ignore ID 1 and 2 for startup sequence
     */
    RTS_INVALID_ID = NOMAD_RTS_CODE_BLOCK(0),
    STARTUP_SEQUENCE_A,
    STARTUP_SEQUENCE_B,
    REGULAR_SYSTEM_CLEANUP_A,
    REGULAR_SYSTEM_CLEANUP_B,
    REGULAR_SYSTEM_DIAGNOSTIC_A,
    REGULAR_SYSTEM_DIAGNOSTIC_B,

    /**
     * @section B: Reseverd for system
     *
     */
    RESERVED_SYSTEM_SEQUENCE = NOMAD_RTS_CODE_BLOCK(5),

    /**
     * @section C: Mission Planning
     *
     */
    PLANNING_CUSTOM_ACTION_A = NOMAD_RTS_CODE_BLOCK(10),
    PLANNING_CUSTOM_ACTION_B,
    PLANNING_CUSTOM_ACTION_C,
    PLANNING_CUSTOM_NUM,

    PLANNING_RTS_VERIFY_START = NOMAD_RTS_CODE_BLOCK(11),
    PLANNING_RTS_VERIFY_CDH_COND,
    PLANNING_RTS_VERIFY_AHRS_COND,
    PLANNING_RTS_VERIFY_GPSR_COND,
    PLANNING_RTS_VERIFY_MOBM_COND,
    PLANNING_RTS_VERIFY_MOBM_EYES_COND,
    PLANNING_RTS_VERIFY_SCIE_COND,
    PLANNING_RTS_VERIFY_SCIE_ARM_COND,
    PLANNING_RTS_VERIFY_SCIE_EYES_COND,
    PLANNING_RTS_VERIFY_SCIE_DRILL_COND,
    PLANNING_RTS_VERIFY_ENV_COND,
    PLANNING_RTS_VERIFY_NUM,

    /**
     * @section D: Mission Orchestrator
     *
     */
    ORCHESTRA_CUSTOM_ACTION_A = NOMAD_RTS_CODE_BLOCK(15),
    ORCHESTRA_CUSTOM_ACTION_B,
    ORCHESTRA_CUSTOM_ACTION_C,
    ORCHESTRA_CUSTOM_NUM,

    ORCHESTRA_RTS_EXAMPLE_A = NOMAD_RTS_CODE_BLOCK(16),
    ORCHESTRA_RTS_EXAMPLE_B,
    ORCHESTRA_RTS_EXAMPLE_C,
    ORCHESTRA_RTS_EXAMPLE_D,
    ORCHESTRA_RTS_EXAMPLE_E,
    ORCHESTRA_RTS_EXAMPLE_F,
    ORCHESTRA_RTS_NUM,

    /**
     * @section E: Reseverd at 20
     *
     */

    /**
     * @section F: Reseverd at 25
     *
     */

    /**
     * @section G: Reseverd at 30
     *
     */
} NOMAD_ScRtsId_t;

typedef enum
{
    /**
     * @section A: Nominal actions, start at 0
     * We ignore ID 1 and 2 for startup sequence
     */
    ATS_INVALID_ID = NOMAD_RTS_CODE_BLOCK(0),
} NOMAD_ScAtsId_t;

#endif