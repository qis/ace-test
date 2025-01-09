project(ace-jpeg-turbo LANGUAGES CXX)
include(${CMAKE_CURRENT_LIST_DIR}/../common.cmake)

find_package(libjpeg-turbo CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE libjpeg-turbo::turbojpeg-static)
