cmake_minimum_required(VERSION 3.16)

project(pa10mini_ctests LANGUAGES CXX)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    include(CTest)
endif()

add_executable(ctest_manzhuk
    ctest_manzhuk.cpp
    ctest_manzhuk.h
    ../pa10mini/manzhuk/manzhuk.h
)

set_target_properties(ctest_manzhuk PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
target_compile_definitions(ctest_manzhuk PRIVATE MANZHUK_TEST)
target_include_directories(ctest_manzhuk PRIVATE
    ../pa10mini
    ../pa10mini/manzhuk
)

# Use the same prebuilt solver as the application on Windows.
if(WIN32)
    set(PA10MINI_MANZHUK_LIBRARY
        "${CMAKE_CURRENT_LIST_DIR}/../pa10mini/manzhuk/manzhuk.lib"
        CACHE FILEPATH "Prebuilt Manzhuk library for the selected Windows compiler and architecture"
    )
    if(NOT EXISTS "${PA10MINI_MANZHUK_LIBRARY}")
        message(FATAL_ERROR "Manzhuk library not found: ${PA10MINI_MANZHUK_LIBRARY}")
    endif()
    if(NOT TARGET manzhuk)
        add_library(manzhuk STATIC IMPORTED)
        set_target_properties(manzhuk PROPERTIES
            IMPORTED_LOCATION "${PA10MINI_MANZHUK_LIBRARY}"
        )
    endif()
    target_link_libraries(ctest_manzhuk PRIVATE manzhuk)
else()
    # TODO: Provide and link a prebuilt Manzhuk library on Linux.
endif()

if(BUILD_TESTING)
    add_test(NAME ctest_manzhuk COMMAND ctest_manzhuk)
    set_tests_properties(ctest_manzhuk PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    )
endif()
