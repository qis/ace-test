cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(ace-test VERSION 0.1.0 LANGUAGES CXX)

# Version
configure_file(res/version.h.in ${CMAKE_CURRENT_BINARY_DIR}/src/version.h LF)

# Warning Options
set(WARNING_OPTIONS -Wall -Wextra -Wpedantic -Werror -Wno-unused-parameter -Wno-unused-variable)

# Library
add_library(library src/library.hpp src/library.cpp)
target_compile_definitions(library PRIVATE LIBRARY_BUILD NOMINMAX WIN32_LEAN_AND_MEAN)
target_compile_options(library PRIVATE ${WARNING_OPTIONS})

target_include_directories(library PRIVATE src PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/src>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:include>)

if(BUILD_SHARED_LIBS)
  set_target_properties(library PROPERTIES DEFINE_SYMBOL LIBRARY_EXPORTS)
  target_compile_definitions(library PUBLIC LIBRARY_SHARED)
  if(NOT WIN32)
    target_compile_options(library PRIVATE -fvisibility=hidden)
  endif()
endif()

# Dependencies
find_package(fmt REQUIRED)
target_link_libraries(library PUBLIC fmt::fmt)

if(NOT WIN32)
  target_link_libraries(library PUBLIC dl)
endif()

# Wine
set(WINE WINEPATH=$ENV{ACE}/msvc/bin WINEDEBUG=-all wine)

# Main
add_executable(main src/main.cpp src/main.manifest src/main.rc)
target_compile_definitions(main PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
target_compile_options(main PRIVATE ${WARNING_OPTIONS})
target_link_libraries(main PRIVATE library)

if(WIN32 AND CMAKE_HOST_SYSTEM_NAME STREQUAL Linux)
  add_custom_target(run-main COMMENT "Running main.exe ..."
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} USES_TERMINAL
    COMMAND ${CMAKE_COMMAND} -E env ${WINE} $<TARGET_FILE:main>)
else()
  add_custom_target(run-main COMMENT "Running main ..."
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} USES_TERMINAL
    COMMAND $<TARGET_FILE:main>)
endif()

# Benchmarks
add_executable(benchmarks src/benchmarks.cpp src/main.manifest)
target_compile_definitions(benchmarks PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
target_compile_options(benchmarks PRIVATE ${WARNING_OPTIONS})

find_package(benchmark REQUIRED)
target_link_libraries(benchmarks PRIVATE library benchmark::benchmark)

if(WIN32 AND CMAKE_HOST_SYSTEM_NAME STREQUAL Linux)
  add_custom_target(run-benchmarks COMMENT "Running benchmarks.exe ..."
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} USES_TERMINAL
    COMMAND ${CMAKE_COMMAND} -E env ${WINE} $<TARGET_FILE:benchmarks>)
else()
  add_custom_target(run-benchmarks COMMENT "Running benchmarks ..."
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} USES_TERMINAL
    COMMAND $<TARGET_FILE:benchmarks>)
endif()

# Tests
add_executable(tests src/tests.cpp src/main.manifest)
target_compile_definitions(tests PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
target_compile_options(tests PRIVATE ${WARNING_OPTIONS})

find_package(doctest REQUIRED)
target_link_libraries(tests PRIVATE library doctest::doctest)
doctest_discover_tests(tests WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

if(WIN32 AND CMAKE_HOST_SYSTEM_NAME STREQUAL Linux)
  add_custom_target(run-tests COMMENT "Running tests.exe ..."
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} USES_TERMINAL
    COMMAND ${CMAKE_COMMAND} -E env ${WINE} $<TARGET_FILE:tests>)
else()
  add_custom_target(run-tests COMMENT "Running tests ..."
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} USES_TERMINAL
    COMMAND $<TARGET_FILE:tests>)
endif()
