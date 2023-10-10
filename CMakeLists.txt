cmake_minimum_required(VERSION 3.9)
project(NormalModeCartesianTransformation VERSION 0.1.0 LANGUAGES C CXX DESCRIPTION "libNormalModeCartesianTransformation")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(GNUInstallDirs)

# compiller options
add_compile_options(-Wall -Wextra -Wpedantic) # Warning
add_compile_options(--std=c++17)              # CXX standard
add_compile_options(-O3)                      # Compiler optimization option

find_package(Eigen3 REQUIRED)
find_package(FFTW REQUIRED) # This directly finds FFTW3

# include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${EIGEN3_INCLUDE_DIRS}
    ${FFTW_INCLUDE_DIRS}
)

add_library(NormalModeCartesianTransformation SHARED
     ${CMAKE_CURRENT_SOURCE_DIR}/src/FFTTransformation.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/src/ExplicitTransformation.cpp
)

target_link_libraries(NormalModeCartesianTransformation PRIVATE FFTW::Double)

add_executable(test_benchmark test_benchmark.cpp)
target_link_libraries(test_benchmark PRIVATE NormalModeCartesianTransformation)

add_executable(test_consistency test_consistency.cpp)
target_link_libraries(test_consistency PRIVATE NormalModeCartesianTransformation)

add_executable(test test.cpp)
target_link_libraries(test PRIVATE NormalModeCartesianTransformation)

# add_executable(test_explicit test_explicit.cpp)
# target_link_libraries(test_explicit PRIVATE NormalModeCartesianTransformation)

# include(CTest)
# enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
