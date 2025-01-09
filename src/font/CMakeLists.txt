project(ace-font LANGUAGES CXX)
include(${CMAKE_CURRENT_LIST_DIR}/../common.cmake)

find_package(PNG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE PNG::PNG)

find_package(Freetype REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Freetype::Freetype)

find_package(harfbuzz CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE harfbuzz::harfbuzz-subset)
#target_link_libraries(${PROJECT_NAME} PRIVATE harfbuzz::harfbuzz)
