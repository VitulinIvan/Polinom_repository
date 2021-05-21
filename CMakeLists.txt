cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME Polinom)
project(${PROJECT_NAME})

set(List List)
set(Polinom Polinom)
set(main main)

# TODO(Kornyakov): not sure if these lines are needed
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/List ${CMAKE_CURRENT_SOURCE_DIR}/Polinom) 

# BUILD
add_subdirectory(List) 
add_subdirectory(Polinom)
add_subdirectory(main)
add_subdirectory(gtest)
add_subdirectory(test)

# REPORT
message( STATUS "")
message( STATUS "General configuration for ${PROJECT_NAME}")
message( STATUS "======================================")
message( STATUS "")
message( STATUS "   Configuration: ${CMAKE_BUILD_TYPE}")
message( STATUS "")
