# This example toolchain file describes the cross compiler to use for
# the target architecture indicated in the configuration file.

# In this sample application, the cross toolchain is configured to
# use a cross compiler for the PowerPC 440 processor which is used on
# the IBM "Bamboo" development board.  The GCC toolchain is named
# accordingly and assumed to be installed in "/opt/x-tools".

# Basic cross system configuration
set(PPC440_BR_TOP "$ENV{PPC440_BR_TOP}"
    CACHE PATH "Top directory for Linux buildroot filesystem project")

set(CMAKE_SYSTEM_NAME			Linux)
set(CMAKE_SYSTEM_VERSION		1)
set(CMAKE_SYSTEM_PROCESSOR		powerpc)

# specify the cross compiler - adjust accord to compiler installation
# This uses the compiler-wrapper toolchain that buildroot produces
set(CMAKE_C_COMPILER			"${PPC440_BR_TOP}/host/usr/bin/powerpc-440_softfp-linux-gnu-gcc")
set(CMAKE_CXX_COMPILER			"${PPC440_BR_TOP}/host/usr/bin/powerpc-440_softfp-linux-gnu-g++")

# where is the target environment
set(CMAKE_FIND_ROOT_PATH		"/opt/x-tools/powerpc-440_softfp-linux-gnu/powerpc-440_softfp-linux-gnu/sysroot"
                                "${PPC440_BR_TOP}/staging")

# search for programs in the build host directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM	NEVER)

# for libraries and headers in the target directories
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY	ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE	ONLY)

# these settings are specific to cFE/OSAL and determines
# which abstraction layers are built when this toolchain is used
set(CFE_SYSTEM_PSPNAME			pc-linux)
set(OSAL_SYSTEM_OSTYPE			posix)
