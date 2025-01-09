project(ace-deflate LANGUAGES CXX)
include(${CMAKE_CURRENT_LIST_DIR}/../common.cmake)

find_package(libdeflate CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE libdeflate::libdeflate_static)
