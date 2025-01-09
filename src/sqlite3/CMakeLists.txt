project(ace-sqlite3 LANGUAGES CXX)
include(${CMAKE_CURRENT_LIST_DIR}/../common.cmake)

find_package(SQLite3 REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SQLite::SQLite3)

find_program(SQLITE3 sqlite3 REQUIRED)
