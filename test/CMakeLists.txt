#-------------------------------------------------------------------------------
#
#  CMake Config
#
#  fastcluster Tests
#
#-------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.1)

#include(CheckCXXCompilerFlag)
#CHECK_CXX_COMPILER_FLAG("-ansi" COMPILER_SUPPORTS_ANSICXX)
#CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
#if(COMPILER_SUPPORTS_CXX11)
#  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ansi")
#else()
#  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
#endif()

include_directories(include)
include_directories(../src)
include_directories(../include)

file(GLOB ALL_SRCS ../src/fastcluster.cpp)
file(GLOB ALL_TESTS ./test_*.cpp */test_*.cpp)
add_executable(unit_tests unit_tests.cpp ${ALL_SRCS} ${ALL_TESTS})
#target_link_libraries(unit_tests ${Boost_LIBRARIES} ${OSMIUM_LIBRARIES})
add_test(NAME unit_tests COMMAND unit_tests)

target_compile_features(unit_tests PUBLIC cxx_nullptr)

message("-- CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
