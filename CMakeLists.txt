cmake_minimum_required(VERSION 3.0.0)
project(tree_example VERSION 0.1.0 LANGUAGES C CXX)

add_subdirectory("tree")

include(CTest)
enable_testing()

add_executable(tree_example "main.cpp")

target_link_libraries(tree_example tree)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
