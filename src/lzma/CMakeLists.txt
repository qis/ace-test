project(ace-lzma LANGUAGES CXX)
include(${CMAKE_CURRENT_LIST_DIR}/../common.cmake)

find_package(LibLZMA REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE LibLZMA::LibLZMA)
