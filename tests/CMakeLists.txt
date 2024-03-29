cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
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
set(SOURCE_FILES ./coffee.cpp)
add_executable(coffee ${CMAKE_CURRENT_SOURCE_DIR}/coffee.cpp)
add_dependencies(coffee extern_smooth extern_commonutils)
target_link_libraries(coffee ${GITHOME_MSU}/smooth/software/lib/libsmooth.a  ${GITHOME_MSU}/commonutils/software/lib/libmsu_commonutils.a ${GSL_LIBRARY} ${GSL_CBLAS_LIBRARY} ${EIGEN3_LIBRARY})


#################################################
set(SOURCE_FILES ./coffee2.cpp)
add_executable(coffee2 ${CMAKE_CURRENT_SOURCE_DIR}/coffee2.cpp)
add_dependencies(coffee2 extern_smooth extern_commonutils)
target_link_libraries(coffee2 ${GITHOME_MSU}/smooth/software/lib/libsmooth.a  ${GITHOME_MSU}/commonutils/software/lib/libmsu_commonutils.a ${GSL_LIBRARY} ${GSL_CBLAS_LIBRARY} ${EIGEN3_LIBRARY})

#################################################
set(SOURCE_FILES ./keepscore.cc)
add_executable(keepscore ${CMAKE_CURRENT_SOURCE_DIR}/keepscore.cc)
add_dependencies(keepscore extern_smooth extern_commonutils)
target_link_libraries(keepscore ${GITHOME_MSU}/smooth/software/lib/libsmooth.a ${GITHOME_MSU}/commonutils/software/lib/libmsu_commonutils.a ${GSL_LIBRARY} ${GSL_CBLAS_LIBRARY} ${EIGEN3_LIBRARY})

#################################################
set(SOURCE_FILES ./obs_test1.cc)
add_executable(obs_test1 ${CMAKE_CURRENT_SOURCE_DIR}/obs_test1.cc)
add_dependencies(obs_test1 extern_smooth extern_commonutils)
target_link_libraries(obs_test1 ${GITHOME_MSU}/smooth/software/lib/libsmooth.a ${GITHOME_MSU}/commonutils/software/lib/libmsu_commonutils.a ${GSL_LIBRARY} ${GSL_CBLAS_LIBRARY} ${EIGEN3_LIBRARY})

#################################################
set(SOURCE_FILES ./tea.cc)
add_executable(tea ${CMAKE_CURRENT_SOURCE_DIR}/tea.cc)
add_dependencies(tea extern_smooth extern_commonutils)
target_link_libraries(tea ${GITHOME_MSU}/smooth/software/lib/libsmooth.a ${GITHOME_MSU}/commonutils/software/lib/libmsu_commonutils.a ${GSL_LIBRARY} ${GSL_CBLAS_LIBRARY} ${EIGEN3_LIBRARY})
