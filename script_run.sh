#!/bin/bash

# Default directory
MISSION="cpu1"
DEBUG=false

# Check if an argument is provided
if [ $# -gt 0 ]; then
    if [ $1 = "DEBUG" ]; then
        echo "DEBUG Flag Enable"
        DEBUG=true
    else
        MISSION=$1
    fi
fi

echo "Using directory: $MISSION"

cd build/exe/$MISSION

echo "Running Flight Software"
if [ $DEBUG = true ]; then
    sudo gdb ./core-$MISSION
else
    sudo taskset -c 0 ./core-$MISSION
fi