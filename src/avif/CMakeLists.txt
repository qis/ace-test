project(ace-avif LANGUAGES CXX)
include(${CMAKE_CURRENT_LIST_DIR}/../common.cmake)

find_package(libavif CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE avif)
