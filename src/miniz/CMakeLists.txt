project(ace-miniz LANGUAGES CXX)
include(${CMAKE_CURRENT_LIST_DIR}/../common.cmake)

find_package(miniz CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE miniz::miniz)
