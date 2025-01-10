add_library(${PROJECT_NAME} SHARED
  ${CMAKE_SOURCE_DIR}/src/main.manifest
  ${CMAKE_SOURCE_DIR}/src/test.cpp)

target_sources(${PROJECT_NAME} PUBLIC FILE_SET CXX_MODULES FILES main.ccm)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_26)

set_target_properties(${PROJECT_NAME} PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
  CXX_VISIBILITY_PRESET hidden)

if(WIN32)
  target_compile_definitions(${PROJECT_NAME} PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
endif()

add_dependencies(ace ${PROJECT_NAME})
