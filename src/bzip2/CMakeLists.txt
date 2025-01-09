project(ace-bzip2 LANGUAGES CXX)
include(${CMAKE_CURRENT_LIST_DIR}/../common.cmake)

find_package(BZip2 REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE BZip2::BZip2)
