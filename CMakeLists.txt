cmake_minimum_required(VERSION 3.30 FATAL_ERROR)
project(ace DESCRIPTION "Ace" VERSION 0.1.0 LANGUAGES CXX)

# Version
set(PROJECT_VENDOR "Vendor")
configure_file(res/version.h.in ${CMAKE_CURRENT_BINARY_DIR}/src/version.h LF)

# Application
add_executable(ace src/main.cpp src/main.rc)
target_include_directories(ace PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/src)
target_compile_features(ace PRIVATE cxx_std_26)

if(WIN32)
  target_compile_definitions(ace PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
endif()

# Emulator
if(CMAKE_HOST_UNIX AND WIN32)
  add_custom_target(wine
    COMMAND ${CMAKE_CROSSCOMPILING_EMULATOR} $<TARGET_FILE:ace>
    USES_TERMINAL)
endif()

# Tests
include(CTest)
find_package(doctest CONFIG REQUIRED)
target_link_libraries(ace PRIVATE doctest::doctest)

if(CMAKE_HOST_SYSTEM_NAME STREQUAL CMAKE_SYSTEM_NAME)
  include(doctest)
  doctest_discover_tests(ace WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endif()

# Dependencies
find_package(Threads REQUIRED)
target_link_libraries(ace PRIVATE Threads::Threads)

add_subdirectory(src/libxml2)
target_link_libraries(ace PRIVATE ace-libxml2)

add_subdirectory(src/pugixml)
target_link_libraries(ace PRIVATE ace-pugixml)
