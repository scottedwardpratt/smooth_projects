cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
set(CMAKE_VERBOSE_MAKEFILE on)
project(smooth)
set(GITHOME_MSU $ENV{GITHOME_MSU})

add_custom_target(extern_commonutils COMMAND make WORKING_DIRECTORY ${GITHOME_MSU}/commonutils/software)
add_custom_target(extern_smooth COMMAND make WORKING_DIRECTORY ${GITHOME_MSU}/smooth/software)

set(CMAKE_CXX_FLAGS "-W -Wall -march=native -std=c++17 -O2")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
find_package(GSL REQUIRED)
find_package(Eigen3 REQUIRED)
include_directories(SYSTEM ${GSL_INCLUDE_DIR} ${EIGEN3_INCLUDE_DIR} ${GITHOME_MSU}/commonutils/software/include ${GITHOME_MSU}/smooth/software/include)

link_directories(${GITHOME_MSU}/smooth/software/lib ${GITHOME_MSU}/commonutils/software/lib)

find_library(${GITHOME_MSU}/commonutils/software/lib msu_commonutils)
find_library(${GITHOME_MSU}/smooth/software/lib smooth)

#################################################
set(SOURCE_FILES ./PCA_test.cc)
add_executable(PCA_test ${CMAKE_CURRENT_SOURCE_DIR}/PCA_test.cc)
add_dependencies(PCA_test extern_smooth extern_commonutils)
target_link_libraries(PCA_test ${GITHOME_MSU}/smooth/software/lib/libsmooth.a  ${GITHOME_MSU}/commonutils/software/lib/libmsu_commonutils.a ${GSL_LIBRARY} ${GSL_CBLAS_LIBRARY} ${EIGEN3_LIBRARY})
