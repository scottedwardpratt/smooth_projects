cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(CMAKE_VERBOSE_MAKEFILE on)
project(smooth_mainprograms CXX)
set(GITHOME_BAND_SMOOTH $ENV{GITHOME_BAND_SMOOTH})
set (MAIN_PROGRAM_DIR "main_programs")
set (TUTORIAL_PROGRAM_DIR "tutorial_programs")
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
# trainingpoint_optimizer
#################################################
set(SOURCE_FILES ${MAIN_PROGRAM_DIR}/trainingpoint_optimizer_main.cc)
add_executable(trainingpoint_optimizer ${MAIN_PROGRAM_DIR}/trainingpoint_optimizer_main.cc)
add_dependencies(trainingpoint_optimizer extern_smooth)
target_link_libraries(trainingpoint_optimizer ${GITHOME_BAND_SMOOTH}/software/lib/libsmooth.a  ${GITHOME_BAND_SMOOTH}/software/lib/libmsu_smoothutils.a   ${EIGEN3_LIBRARY})


#################################################
# smoothy_testattrainingpts
#################################################
set(SOURCE_FILES ${MAIN_PROGRAM_DIR}/smoothy_testattrainingpts_main.cc)
add_executable(smoothy_testattrainingpts ${MAIN_PROGRAM_DIR}/smoothy_testattrainingpts_main.cc)
add_dependencies(smoothy_testattrainingpts extern_smooth)
target_link_libraries(smoothy_testattrainingpts ${GITHOME_BAND_SMOOTH}/software/lib/libsmooth.a  ${GITHOME_BAND_SMOOTH}/software/lib/libmsu_smoothutils.a   ${EIGEN3_LIBRARY})

#################################################
# smoothy_testvsfullmodel
#################################################
set(SOURCE_FILES ${MAIN_PROGRAM_DIR}/smoothy_testvsfullmodel_main.cc)
add_executable(smoothy_testvsfullmodel ${MAIN_PROGRAM_DIR}/smoothy_testvsfullmodel_main.cc)
add_dependencies(smoothy_testvsfullmodel extern_smooth)
target_link_libraries(smoothy_testvsfullmodel ${GITHOME_BAND_SMOOTH}/software/lib/libsmooth.a  ${GITHOME_BAND_SMOOTH}/software/lib/libmsu_smoothutils.a   ${EIGEN3_LIBRARY})

#################################################
# smoothy_calcobs
#################################################
set(SOURCE_FILES ${MAIN_PROGRAM_DIR}/smoothy_calcobs_main.cc)
add_executable(smoothy_calcobs ${MAIN_PROGRAM_DIR}/smoothy_calcobs_main.cc)
add_dependencies(smoothy_calcobs extern_smooth)
target_link_libraries(smoothy_calcobs ${GITHOME_BAND_SMOOTH}/software/lib/libsmooth.a ${GITHOME_BAND_SMOOTH}/software/lib/libmsu_smoothutils.a   ${EIGEN3_LIBRARY})

#################################################
# mcmc
#################################################
set(SOURCE_FILES ${MAIN_PROGRAM_DIR}/smoothy_mcmc_main.cc)
add_executable(smoothy_mcmc ${MAIN_PROGRAM_DIR}/smoothy_mcmc_main.cc)
add_dependencies(smoothy_mcmc extern_smooth)
target_link_libraries(smoothy_mcmc ${GITHOME_BAND_SMOOTH}/software/lib/libsmooth.a ${GITHOME_BAND_SMOOTH}/software/lib/libmsu_smoothutils.a   ${EIGEN3_LIBRARY})

#################################################
# fake full model
#################################################
set(SOURCE_FILES ${TUTORIAL_PROGRAM_DIR}/fakefullmodel.cc)
add_executable(fakefullmodel ${TUTORIAL_PROGRAM_DIR}/fakefullmodel.cc)
add_dependencies(fakefullmodel extern_smooth)
target_link_libraries(fakefullmodel
${GITHOME_BAND_SMOOTH}/software/lib/libsmooth.a ${GITHOME_BAND_SMOOTH}/software/lib/libmsu_smoothutils.a ${EIGEN3_LIBRARY})

#################################################
# create fake info files
#################################################
set(SOURCE_FILES ${TUTORIAL_PROGRAM_DIR}/fakeinfo.cc)
add_executable(fakeinfo ${TUTORIAL_PROGRAM_DIR}/fakeinfo.cc)
add_dependencies(fakeinfo extern_smooth)
target_link_libraries(fakeinfo
${GITHOME_BAND_SMOOTH}/software/lib/libsmooth.a ${GITHOME_BAND_SMOOTH}/software/lib/libmsu_smoothutils.a ${EIGEN3_LIBRARY})
#################################################
