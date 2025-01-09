project(ace-boost LANGUAGES CXX)
include(${CMAKE_CURRENT_LIST_DIR}/../common.cmake)

find_package(Boost REQUIRED COMPONENTS
  algorithm
  container
  circular_buffer
  json
  url)

target_link_libraries(${PROJECT_NAME} PRIVATE
  Boost::algorithm
  Boost::container
  Boost::circular_buffer
  Boost::json
  Boost::url)
