cmake_minimum_required(VERSION 3.12)

# set name of the project
project(a0)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
set(CMAKE_CXX_STANDARD 17)

# thirdparty code
set(CMM_FETCHCONTENT_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/ext/cache CACHE STRING "Base dir for thirdparty libs" )
add_subdirectory(ext)

# our code
add_subdirectory(src)
