project(ace-svg LANGUAGES CXX)
include(${CMAKE_CURRENT_LIST_DIR}/../common.cmake)

find_package(unofficial-lunasvg CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE unofficial::lunasvg::lunasvg)
