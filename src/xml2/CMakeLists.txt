project(ace-xml2 LANGUAGES CXX)
include(${CMAKE_CURRENT_LIST_DIR}/../common.cmake)

find_package(LibXml2 REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE LibXml2::LibXml2)

find_program(XMLLINT xmllint REQUIRED)
execute_process(COMMAND ${XMLLINT} --noout --nonet --timing ${CMAKE_SOURCE_DIR}/test.xml
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  COMMAND_ERROR_IS_FATAL ANY
  COMMAND_ECHO STDOUT)
