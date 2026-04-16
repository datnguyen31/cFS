# This example toolchain file describes the cross compiler to use for
# the target architecture indicated in the configuration file.

# Basic cross system configuration
set(CMAKE_SYSTEM_NAME           Linux)
set(CMAKE_SYSTEM_VERSION        1)
set(CMAKE_SYSTEM_PROCESSOR      i686)

# Specify the cross compiler executables
# Typically these would be installed in a home directory or somewhere
# in /opt.  However in this example the system compiler is used.
set(CMAKE_C_COMPILER            "/usr/bin/gcc-13")
set(CMAKE_CXX_COMPILER          "/usr/bin/g++-13")

# Configure the find commands
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM   NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY   NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE   NEVER)

# These variable settings are specific to cFE/OSAL and determines which 
# abstraction layers are built when using this toolchain
set(CFE_SYSTEM_PSPNAME      "pc-linux")
set(OSAL_SYSTEM_BSPTYPE     "generic-linux")
set(OSAL_SYSTEM_OSTYPE      "posix")
