cmake_minimum_required(VERSION 3.0.0)
project(tree VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 14)

include(CTest)
enable_testing()

add_library(tree
    "trees/avl.cpp"
    "trees/redblack.cpp"
    
    "tree.cpp"
)

target_include_directories(tree
    PUBLIC "."
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
