cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(CMAKE_VERBOSE_MAKEFILE on)
project(smooth_mainprograms CXX)
set(GITHOME_BAND_SMOOTH $ENV{GITHOME_BAND_SMOOTH})
set (MAIN_PROGRAM_DIR "main_programs")
set (FAKEFULLMODEL_DIR "fakefullmodels")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "$ENV{PWD}/../bin")

add_custom_target(extern_smooth COMMAND make WORKING_DIRECTORY ${GITHOME_BAND_SMOOTH}/software)

message("Will Compile with " ${CMAKE_CXX_COMPILER})
message("For different compiler enter: cmake -D YOUR_PREFERRED_COMPILER .")
set(CMAKE_CXX_FLAGS "-W -Wall -march=native -std=c++20 -O2")
set(CMAKE_MODULE_PATH "${MAIN_PROGRAM_DIR}/cmake")
find_package(Eigen3 REQUIRED)
message("eigen3_include_dir is ${EIGEN3_INCLUDE_DIR}")
include_directories(SYSTEM ${EIGEN3_INCLUDE_DIR} ${GITHOME_BAND_SMOOTH}/software/include $ENV{EIGEN3_INCLUDE_DIR})      
link_directories(${GITHOME_BAND_SMOOTH}/software/lib)

find_library(${GITHOME_BAND_SMOOTH}/software/lib msu_smoothutils)
find_library(${GITHOME_BAND_SMOOTH}/software/lib msu_smooth)

#################################################
set(SOURCE_FILES ${MAIN_PROGRAM_DIR}/trainingpoint_optimizer_main.cc)
add_executable(trainingpoint_optimizer ${MAIN_PROGRAM_DIR}/trainingpoint_optimizer_main.cc)
add_dependencies(trainingpoint_optimizer extern_smooth)
target_link_libraries(trainingpoint_optimizer ${GITHOME_BAND_SMOOTH}/software/lib/libsmooth.a  ${GITHOME_BAND_SMOOTH}/software/lib/libmsu_smoothutils.a   ${EIGEN3_LIBRARY})
#################################################
set(SOURCE_FILES ${MAIN_PROGRAM_DIR}/smoothy_tune_main.cc)
add_executable(smoothy_tune ${MAIN_PROGRAM_DIR}/smoothy_tune_main.cc)
add_dependencies(smoothy_tune extern_smooth)
target_link_libraries(smoothy_tune ${GITHOME_BAND_SMOOTH}/software/lib/libsmooth.a  ${GITHOME_BAND_SMOOTH}/software/lib/libmsu_smoothutils.a   ${EIGEN3_LIBRARY})
#################################################
set(SOURCE_FILES ${MAIN_PROGRAM_DIR}/smoothy_testvsfullmodel_main.cc)
add_executable(smoothy_testvsfullmodel ${MAIN_PROGRAM_DIR}/smoothy_testvsfullmodel_main.cc)
add_dependencies(smoothy_testvsfullmodel extern_smooth)
target_link_libraries(smoothy_testvsfullmodel ${GITHOME_BAND_SMOOTH}/software/lib/libsmooth.a  ${GITHOME_BAND_SMOOTH}/software/lib/libmsu_smoothutils.a   ${EIGEN3_LIBRARY})
#################################################
set(SOURCE_FILES ${MAIN_PROGRAM_DIR}/smoothy_testvsfullmodelalt_main.cc)
add_executable(smoothy_testvsfullmodelalt ${MAIN_PROGRAM_DIR}/smoothy_testvsfullmodelalt_main.cc)
add_dependencies(smoothy_testvsfullmodelalt extern_smooth)
target_link_libraries(smoothy_testvsfullmodelalt ${GITHOME_BAND_SMOOTH}/software/lib/libsmooth.a  ${GITHOME_BAND_SMOOTH}/software/lib/libmsu_smoothutils.a   ${EIGEN3_LIBRARY})
#################################################
set(SOURCE_FILES ${MAIN_PROGRAM_DIR}/smoothy_vslambda_main.cc)
add_executable(smoothy_vslambda ${MAIN_PROGRAM_DIR}/smoothy_vslambda_main.cc)
add_dependencies(smoothy_vslambda extern_smooth)
target_link_libraries(smoothy_vslambda ${GITHOME_BAND_SMOOTH}/software/lib/libsmooth.a  ${GITHOME_BAND_SMOOTH}/software/lib/libmsu_smoothutils.a   ${EIGEN3_LIBRARY})
#################################################
set(SOURCE_FILES ${MAIN_PROGRAM_DIR}/smoothy_testsigma_main.cc)
add_executable(smoothy_testsigma ${MAIN_PROGRAM_DIR}/smoothy_testsigma_main.cc)
add_dependencies(smoothy_testsigma extern_smooth)
target_link_libraries(smoothy_testsigma ${GITHOME_BAND_SMOOTH}/software/lib/libsmooth.a  ${GITHOME_BAND_SMOOTH}/software/lib/libmsu_smoothutils.a   ${EIGEN3_LIBRARY})
#################################################
set(SOURCE_FILES ${MAIN_PROGRAM_DIR}/smoothy_calcobs_main.cc)
add_executable(smoothy_calcobs ${MAIN_PROGRAM_DIR}/smoothy_calcobs_main.cc)
add_dependencies(smoothy_calcobs extern_smooth)
target_link_libraries(smoothy_calcobs ${GITHOME_BAND_SMOOTH}/software/lib/libsmooth.a ${GITHOME_BAND_SMOOTH}/software/lib/libmsu_smoothutils.a   ${EIGEN3_LIBRARY})
#################################################
set(SOURCE_FILES ${MAIN_PROGRAM_DIR}/smoothy_surmise_calcobs_main.cc)
add_executable(smoothy_surmise_calcobs ${MAIN_PROGRAM_DIR}/smoothy_surmise_calcobs_main.cc)
add_dependencies(smoothy_surmise_calcobs extern_smooth)
target_link_libraries(smoothy_surmise_calcobs ${GITHOME_BAND_SMOOTH}/software/lib/libsmooth.a ${GITHOME_BAND_SMOOTH}/software/lib/libmsu_smoothutils.a   ${EIGEN3_LIBRARY})
#################################################
set(SOURCE_FILES ${MAIN_PROGRAM_DIR}/mcmc_main.cc)
add_executable(mcmc ${MAIN_PROGRAM_DIR}/mcmc_main.cc)
add_dependencies(mcmc extern_smooth)
target_link_libraries(mcmc ${GITHOME_BAND_SMOOTH}/software/lib/libsmooth.a ${GITHOME_BAND_SMOOTH}/software/lib/libmsu_smoothutils.a   ${EIGEN3_LIBRARY})
#################################################
#
# Some fake full models (for tutorial or emulator-testing purposes
#################################################
# fakesmooth
#################################################
set(SOURCE_FILES ${FAKEFULLMODEL_DIR}/fakesmooth.cc)
add_executable(fakesmooth ${FAKEFULLMODEL_DIR}/fakesmooth.cc)
add_dependencies(fakesmooth extern_smooth)
target_link_libraries(fakesmooth 
${GITHOME_BAND_SMOOTH}/software/lib/libsmooth.a ${GITHOME_BAND_SMOOTH}/software/lib/libmsu_smoothutils.a ${EIGEN3_LIBRARY})
#################################################
# fake
#################################################
set(SOURCE_FILES ${FAKEFULLMODEL_DIR}/fake.cc)
add_executable(fake ${FAKEFULLMODEL_DIR}/fake.cc)
add_dependencies(fake extern_smooth)
target_link_libraries(fake ${GITHOME_BAND_SMOOTH}/software/lib/libmsu_smoothutils.a
 ${EIGEN3_LIBRARY})
#################################################
# fakerhic
#################################################
set(SOURCE_FILES ${FAKEFULLMODEL_DIR}/fakerhic.cc)
add_executable(fakerhic ${FAKEFULLMODEL_DIR}/fakerhic.cc)
add_dependencies(fakerhic extern_smooth)
target_link_libraries(fakerhic ${GITHOME_BAND_SMOOTH}/software/lib/libmsu_smoothutils.a
 ${EIGEN3_LIBRARY})
#################################################
