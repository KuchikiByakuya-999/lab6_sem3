cmake_minimum_required(VERSION 3.10)
project(warcraft3_db)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PQXX REQUIRED libpqxx)

add_executable(app main.cpp)

target_include_directories(app PRIVATE ${PQXX_INCLUDE_DIRS})
target_link_libraries(app PRIVATE ${PQXX_LIBRARIES})
