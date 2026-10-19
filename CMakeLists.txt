cmake_minimum_required(VERSION 3.16)

project(pa10mini_all LANGUAGES CXX)

include(CTest)

add_subdirectory(pa10mini)

if(BUILD_TESTING)
    add_subdirectory(tests)
    add_subdirectory(ctests)
endif()
