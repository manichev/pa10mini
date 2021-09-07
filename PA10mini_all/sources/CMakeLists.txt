cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

project(PA10mini LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

################################################################################
# Set target arch type if empty. Visual studio solution generator provides it.
################################################################################
if(NOT CMAKE_VS_PLATFORM_NAME)
    set(CMAKE_VS_PLATFORM_NAME "x64")
endif()
message("${CMAKE_VS_PLATFORM_NAME} architecture in use")

#if(NOT ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Pocket PC 2003 (ARMV4)"
#     OR "${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32"))
#    message(FATAL_ERROR "${CMAKE_VS_PLATFORM_NAME} arch is not supported!")
#endif()

################################################################################
# Global configuration types
################################################################################
set(CMAKE_CONFIGURATION_TYPES
    "Debug"
    "Release"
    CACHE STRING "" FORCE
)

################################################################################
# Global compiler options
################################################################################
if(MSVC)
    # remove default flags provided with CMake for MSVC
endif()

################################################################################
# Global linker options
################################################################################
if(MSVC)
    # remove default flags provided with CMake for MSVC
    set(CMAKE_EXE_LINKER_FLAGS "")
    set(CMAKE_MODULE_LINKER_FLAGS "")
    set(CMAKE_SHARED_LINKER_FLAGS "")
    set(CMAKE_STATIC_LINKER_FLAGS "")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_DEBUG "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_DEBUG "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_RELEASE "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "${CMAKE_STATIC_LINKER_FLAGS}")
endif()

################################################################################
# Nuget packages function stub.
################################################################################
function(use_package TARGET PACKAGE VERSION)
    message(WARNING "No implementation of use_package. Create yours. "
                    "Package \"${PACKAGE}\" with version \"${VERSION}\" "
                    "for target \"${TARGET}\" is ignored!")
endfunction()

################################################################################
# Common utils
################################################################################
#include(CMake/Utils.cmake)

################################################################################
# Additional Global Settings(add specific info there)
################################################################################
include(CMake/GlobalSettingsInclude.cmake OPTIONAL)

################################################################################
# Use solution folders feature
################################################################################
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(qwt)

## Qt5
find_package(Qt5 COMPONENTS Gui Core Widgets OpenGL REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


################################################################################
# Sub-projects
################################################################################
include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/manzhuk/fcttask")
include_directories ("${CMAKE_CURRENT_SOURCE_DIR}/manzhuk")

if (UNIX)
include_directories ("/usr/include/qwt")
endif()

if (WIN32)
include_directories ("C:/Qwt-6.1.4/include")
endif()

list(APPEND pa10_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/solver.cpp
    ${CMAKE_CURRENT_LIST_DIR}/textdriver.cpp
    ${CMAKE_CURRENT_LIST_DIR}/manzhuk/fcttask/fcttask.cpp
    ${CMAKE_CURRENT_LIST_DIR}/manzhuk/manzhuk.cpp
    ${CMAKE_CURRENT_LIST_DIR}/plot.cpp
    ${CMAKE_CURRENT_LIST_DIR}/scanner.cpp
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/parser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/solverparam.cpp
    ${CMAKE_CURRENT_LIST_DIR}/circuititem.cpp
    ${CMAKE_CURRENT_LIST_DIR}/variablechooser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/plotwindow.cpp
    ${CMAKE_CURRENT_LIST_DIR}/daesystem.cpp
    ${CMAKE_CURRENT_LIST_DIR}/expression.cpp
    ${CMAKE_CURRENT_LIST_DIR}/equaledit.cpp
    ${CMAKE_CURRENT_LIST_DIR}/schemeview.cpp
    ${CMAKE_CURRENT_LIST_DIR}/pax_prototype.cpp
    ${CMAKE_CURRENT_LIST_DIR}/circuititemedit.cpp
)

list(APPEND QRCS
    ${CMAKE_CURRENT_LIST_DIR}/pax_prototype.qrc
)

add_executable(PA10mini ${pa10_SOURCES} ${QRCS})

if (MSVC)
    link_directories("C:/Qwt-6.1.4/lib")
    #set (QWTLIBDIR "C:/Qwt-6.1.4/lib")
    target_link_libraries(PA10mini Qt5::Core Qt5::Widgets Qt5::Gui Qt5::OpenGL "C:/Qwt-6.1.4/lib/qwt.lib")
else ()
    target_link_libraries(PA10mini Qt5::Core Qt5::Widgets Qt5::Gui Qt5::OpenGL qwt stdc++ m dl)
endif ()
