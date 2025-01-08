project(ace-bzip2 LANGUAGES CXX)
add_library(${PROJECT_NAME} SHARED main.cpp ${CMAKE_SOURCE_DIR}/src/main.manifest)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_VISIBILITY_PRESET hidden)
target_sources(${PROJECT_NAME} PUBLIC FILE_SET CXX_MODULES FILES main.ccm)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_compile_definitions(${PROJECT_NAME} PRIVATE ACE_EXPORT)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_26)

if(WIN32)
  target_compile_definitions(${PROJECT_NAME} PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
  set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC Threads::Threads)

find_package(BZip2 REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE BZip2::BZip2)
