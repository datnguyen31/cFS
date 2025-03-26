cmake_minimum_required(VERSION 2.6.4)
project(CFE_CPP_APP CXX)

aux_source_directory(fsw/src APP_SRC_FILES)

add_cfe_app(cpp_app ${APP_SRC_FILES})