cmake_minimum_required(VERSION 3.12)

# set name of the project
project(a0)
set(CMAKE_CXX_STANDARD 17)
enable_testing()

# thirdparty code
set(CMM_FETCHCONTENT_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/ext/cache CACHE STRING "Base dir for thirdparty libs" )
add_subdirectory(ext)

# our code
option(CMM_BUILD_GUI "build GUI" ON)
add_subdirectory(src)
