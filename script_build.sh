#!/bin/bash

# Default simulation value
SIMULATION="i686-linux-gnu"

# Check if an argument is provided
if [ $# -gt 0 ]; then
    SIMULATION=$1
fi

echo "Using simulation: $SIMULATION"

make distclean
make SIMULATION=$SIMULATION prep
make install