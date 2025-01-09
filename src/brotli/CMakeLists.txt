project(ace-brotli LANGUAGES CXX)
include(${CMAKE_CURRENT_LIST_DIR}/../common.cmake)

find_package(unofficial-brotli CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE
  unofficial::brotli::brotlidec
  unofficial::brotli::brotlienc)
