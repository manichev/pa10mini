cmake_minimum_required(VERSION 3.16)

project(pa10mini_tests LANGUAGES CXX)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    include(CTest)
endif()

find_package(Qt5 REQUIRED COMPONENTS Core Test)

add_executable(tst_manzhuk
    tst_manzhuk.cpp
    tst_manzhuk.h
    ../pa10mini/manzhuk/manzhuk.h
)

set_target_properties(tst_manzhuk PROPERTIES
    AUTOMOC ON
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
target_compile_definitions(tst_manzhuk PRIVATE MANZHUK_TEST)
target_include_directories(tst_manzhuk PRIVATE
    ../pa10mini
    ../pa10mini/manzhuk
)
target_link_libraries(tst_manzhuk PRIVATE Qt5::Core Qt5::Test)

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
    target_link_libraries(tst_manzhuk PRIVATE manzhuk)
else()
    # TODO: Provide and link a prebuilt Manzhuk library on Linux.
endif()

if(BUILD_TESTING)
    add_test(NAME tst_manzhuk COMMAND tst_manzhuk)
    set_tests_properties(tst_manzhuk PROPERTIES
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    )
endif()
