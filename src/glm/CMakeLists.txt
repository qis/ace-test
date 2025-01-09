project(ace-glm LANGUAGES CXX)
include(${CMAKE_CURRENT_LIST_DIR}/../common.cmake)
target_sources(${PROJECT_NAME} PRIVATE test.cpp)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)

get_target_property(GLM_INCLUDE_DIRECTORIES glm::glm INTERFACE_INCLUDE_DIRECTORIES)
find_file(GLM glm.cppm PATHS ${GLM_INCLUDE_DIRECTORIES} PATH_SUFFIXES glm REQUIRED)
get_filename_component(GLM ${GLM} DIRECTORY)

target_sources(${PROJECT_NAME} PUBLIC FILE_SET
  CXX_MODULES BASE_DIRS ${GLM} FILES ${GLM}/glm.cppm)

target_compile_definitions(${PROJECT_NAME} PRIVATE
  GLM_FORCE_DEPTH_ZERO_TO_ONE
  GLM_FORCE_LEFT_HANDED
  GLM_FORCE_SINGLE_ONLY
  GLM_FORCE_CXX20
  GLM_FORCE_PURE)
