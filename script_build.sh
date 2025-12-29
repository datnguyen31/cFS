#!/usr/bin/env bash
# set -eu pipefail

# Defaults
SIMULATION="i686-linux-gnu"
MISSIONCONFIG="mission_sample"
JOBS=16

usage() {
  cat <<EOF
Usage: $(basename "$0") [OPTIONS]

Options:
  --simulation VALUE        Set SIMULATION (default: $SIMULATION)
  --missionconfig VALUE     Set MISSIONCONFIG (default: $MISSIONCONFIG)
  -j N                      Parallel jobs for make install (default: $JOBS)
  -h, --help                Show this help and exit

Examples:
  $(basename "$0")
  $(basename "$0") --simulation arm-linux-gnueabihf
  $(basename "$0") --missionconfig demo
  $(basename "$0") --missionconfig demo --simulation i686-linux-gnu -j 32

Simulation available option:
  i686-linux-gnu

Mission available option:
  mission_sample
  mission_nomad
EOF
}

# Parse args
while [[ $# -gt 0 ]]; do
  case "$1" in
    -h|--help)
      usage
      exit 0
      ;;
    --simulation=*)
      SIMULATION="${1#*=}"
      shift
      ;;
    --simulation)
      SIMULATION="${2:-}"
      shift 2
      ;;
    --missionconfig=*)
      MISSIONCONFIG="${1#*=}"
      shift
      ;;
    --missionconfig|--mission-config)
      MISSIONCONFIG="${2:-}"
      shift 2
      ;;
    -j)
      JOBS="${2:-}"
      shift 2
      ;;
    -j*)
      JOBS="${1#-j}"
      shift
      ;;
    *)
      echo "Unknown argument: $1" >&2
      usage >&2
      exit 2
      ;;
  esac
done

echo "Using simulation:     $SIMULATION"
echo "Using mission config: $MISSIONCONFIG"
echo "Parallel jobs:        $JOBS"

make distclean
make SIMULATION=$SIMULATION MISSIONCONFIG=$MISSIONCONFIG prep
make -j"$JOBS" install
