cmake_minimum_required(VERSION 3.30 FATAL_ERROR)
project(ace DESCRIPTION "Ace" VERSION 0.1.0 LANGUAGES CXX)

# Version
set(PROJECT_VENDOR "Vendor")
configure_file(res/version.h.in ${CMAKE_CURRENT_BINARY_DIR}/src/version.h LF)

# Application
add_executable(ace src/main.cpp src/main.rc)
target_include_directories(ace PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/src src)
target_compile_features(ace PRIVATE cxx_std_26)

if(WIN32)
  target_compile_definitions(ace PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
else()
  target_link_libraries(ace PRIVATE dl)
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

add_subdirectory(src/xml2)
add_subdirectory(src/pugixml)
add_subdirectory(src/zlib)
add_subdirectory(src/bzip2)
add_subdirectory(src/lzma)
add_subdirectory(src/lz4)
add_subdirectory(src/brotli)
add_subdirectory(src/zstd)
add_subdirectory(src/deflate)
add_subdirectory(src/miniz)
add_subdirectory(src/jpeg)
add_subdirectory(src/jpeg-turbo)
add_subdirectory(src/png)
add_subdirectory(src/avif)
add_subdirectory(src/svg)
add_subdirectory(src/font)
add_subdirectory(src/glm)
add_subdirectory(src/glm-avx2)
