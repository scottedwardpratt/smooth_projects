cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(CMAKE_VERBOSE_MAKEFILE on)
project(smooth_projects)
set(GITHOME_MSU_PRATT $ENV{GITHOME_MSU_PRATT})
set(GITHOME_BAND_SMOOTH $ENV{GITHOME_BAND_SMOOTH})
set (MAIN_PROGRAM_DIR ".")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin")

add_custom_target(extern_commonutils COMMAND make WORKING_DIRECTORY ${GITHOME_MSU_PRATT}/commonutils/software)
add_custom_target(extern_smooth COMMAND make WORKING_DIRECTORY ${GITHOME_BAND_SMOOTH}/software)

find_package(GSL REQUIRED)
find_package(Eigen3 REQUIRED)

set(CMAKE_CXX_FLAGS "-W -Wall -march=native -std=c++17 -O2")
set(CMAKE_MODULE_PATH "${MAIN_PROGRAM_DIR}/cmake")
include_directories(SYSTEM  ${GSL_INCLUDE_DIR} ${EIGEN3_INCLUDE_DIR} ${GITHOME_MSU_PRATT}/commonutils/software/include ${GITHOME_BAND_SMOOTH}/software/include)      
link_directories(${GITHOME_MSU_PRATT}/commonutils/software/lib)

find_library(${GITHOME_MSU_PRATT}/commonutils/software/lib msu_commonutils)

# fakesmooth
#################################################
set(SOURCE_FILES fakesmooth.cc)
add_executable(fakesmooth fakesmooth.cc)
add_dependencies(fakesmooth extern_commonutils extern_smooth)
target_link_libraries(fakesmooth ${GITHOME_MSU_PRATT}/commonutils/software/lib/libmsu_commonutils.a
${GITHOME_BAND_SMOOTH}/software/lib/libsmooth.a ${GSL_LIBRARY} ${GSL_CBLAS_LIBRARY} ${EIGEN3_LIBRARY})
#################################################
# fakerhic
#################################################
set(SOURCE_FILES fakerhic.cc)
add_executable(fakerhic fakerhic.cc)
add_dependencies(fakerhic extern_commonutils)
target_link_libraries(fakerhic ${GITHOME_MSU_PRATT}/commonutils/software/lib/libmsu_commonutils.a
 ${GSL_LIBRARY} ${GSL_CBLAS_LIBRARY} ${EIGEN3_LIBRARY})
#################################################

