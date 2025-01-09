project(ace-lz4 LANGUAGES CXX)
include(${CMAKE_CURRENT_LIST_DIR}/../common.cmake)

find_package(lz4 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE lz4::lz4)
