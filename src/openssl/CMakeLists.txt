project(ace-openssl LANGUAGES CXX)
include(${CMAKE_CURRENT_LIST_DIR}/../common.cmake)

find_package(OpenSSL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE
  OpenSSL::Crypto
  OpenSSL::SSL)

find_program(OPENSSL openssl REQUIRED)
