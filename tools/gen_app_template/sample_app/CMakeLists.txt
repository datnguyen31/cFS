project(CFE_SAMPLE C)

set(APP_SRC_FILES
  fsw/src/sample_app_cmds.c
  fsw/src/sample_app_dispatch.c
  fsw/src/sample_app_scheds.c
  fsw/src/sample_app.c
  fsw/src/sample_utils.c
)

# Create the app module
add_cfe_app(sample ${APP_SRC_FILES})

target_include_directories(sample PUBLIC fsw/inc)
target_include_directories(sample PUBLIC fsw/share)

# If UT is enabled, then add the tests from the subdirectory
# Note that this is an app, and therefore does not provide
# stub functions, as other entities would not typically make
# direct function calls into this application.
if(ENABLE_UNIT_TESTS)
  add_subdirectory(unit-test)
endif(ENABLE_UNIT_TESTS)
