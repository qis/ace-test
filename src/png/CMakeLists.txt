project(ace-png LANGUAGES CXX)
include(${CMAKE_CURRENT_LIST_DIR}/../common.cmake)

find_package(PNG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE PNG::PNG)
