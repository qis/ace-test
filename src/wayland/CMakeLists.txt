project(ace-wayland LANGUAGES CXX)
include(${CMAKE_CURRENT_LIST_DIR}/../common.cmake)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

include(wayland)
target_link_libraries(${PROJECT_NAME} PRIVATE wayland)
