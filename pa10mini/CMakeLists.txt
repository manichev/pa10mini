cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(PA10mini LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qwt's Windows headers export/import symbols for shared builds, which is the
# mode used by its CMake project. This remains configurable via
# -DBUILD_SHARED_LIBS=OFF.
option(BUILD_SHARED_LIBS "Build shared third-party libraries" ON)

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

## Qt5
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets OpenGL Concurrent PrintSupport Svg)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
# AUTOUIC adds its generated include directory automatically. Do not add the
# build root: old qmake ui_*.h files there can shadow the current CMake headers.
set(CMAKE_INCLUDE_CURRENT_DIR OFF)


################################################################################
# Sub-projects
################################################################################
set(PA10MINI_THIRD_PARTY_DIR "${CMAKE_CURRENT_LIST_DIR}/../third_party")
set(PA10MINI_QWT_DIR "${PA10MINI_THIRD_PARTY_DIR}/qwt")
set(PA10MINI_LIBDL_DIR "${PA10MINI_THIRD_PARTY_DIR}/libdl")

foreach(submodule_dir IN ITEMS "${PA10MINI_QWT_DIR}" "${PA10MINI_LIBDL_DIR}")
    if(NOT EXISTS "${submodule_dir}/CMakeLists.txt")
        message(FATAL_ERROR
            "A required dependency submodule is missing or not initialized: ${submodule_dir}.\n"
            "Run 'git submodule update --init --recursive' from the repository root and reconfigure.")
    endif()
endforeach()

# The Qwt CMake subproject supports both Qt 5 and Qt 6, but defaults to Qt 6.
set(QWT_QT_MAJOR_VERSION 5 CACHE STRING "Qt major version used by Qwt" FORCE)
set(WITH_EXAMPLES OFF CACHE BOOL "Build Qwt examples" FORCE)

add_subdirectory("${PA10MINI_QWT_DIR}"
                 "${CMAKE_CURRENT_BINARY_DIR}/third_party/qwt" EXCLUDE_FROM_ALL)

# dlfcn-win32 supplies dlopen/dlsym on Windows. Its subproject is included on
# every platform; its own CMakeLists only creates the library target on Windows.
add_subdirectory("${PA10MINI_LIBDL_DIR}"
                 "${CMAKE_CURRENT_BINARY_DIR}/third_party/libdl" EXCLUDE_FROM_ALL)

# The Qwt CMake port currently adds QWT_DLL definitions unconditionally on
# Windows. Remove its DLL annotations when the consumer requests static libs.
if(WIN32 AND NOT BUILD_SHARED_LIBS)
    set_property(TARGET qwt PROPERTY COMPILE_DEFINITIONS "")
    set_property(TARGET qwt PROPERTY INTERFACE_COMPILE_DEFINITIONS "")
endif()

#add_library(manzhuk STATIC
#    ${CMAKE_CURRENT_LIST_DIR}/manzhuk/manzhuk.cpp
#    ${CMAKE_CURRENT_LIST_DIR}/manzhuk/manzhuk.h
#)

# Use the prebuilt solver on Windows; allow a matching library for each kit.
if(WIN32)
    if(MINGW)
        set(PA10MINI_MANZHUK_DEFAULT_LIBRARY "${CMAKE_CURRENT_LIST_DIR}/manzhuk/libmanzhuk.a")
    else()
        set(PA10MINI_MANZHUK_DEFAULT_LIBRARY "${CMAKE_CURRENT_LIST_DIR}/manzhuk/manzhuk.lib")
    endif()
    set(PA10MINI_MANZHUK_LIBRARY
        "${PA10MINI_MANZHUK_DEFAULT_LIBRARY}"
        CACHE FILEPATH "Prebuilt Manzhuk library for the selected Windows compiler and architecture"
    )
    if(NOT EXISTS "${PA10MINI_MANZHUK_LIBRARY}")
        message(FATAL_ERROR "Manzhuk library not found: ${PA10MINI_MANZHUK_LIBRARY}")
    endif()
    add_library(manzhuk STATIC IMPORTED)
    set_target_properties(manzhuk PROPERTIES
        IMPORTED_LOCATION "${PA10MINI_MANZHUK_LIBRARY}"
    )
endif()

list(APPEND pa10_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/fcttaskcompiler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/fcttaskcompiler.h
    ${CMAKE_CURRENT_LIST_DIR}/solver.cpp
    ${CMAKE_CURRENT_LIST_DIR}/textdriver.cpp
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
    ${CMAKE_CURRENT_LIST_DIR}/settingsdialog.cpp
)

list(APPEND QRCS
    ${CMAKE_CURRENT_LIST_DIR}/pax_prototype.qrc
)

# Keep the forms from pa10mini.pro in the target so AUTOUIC generates their
# headers and Qt Creator exposes them in the project tree.
set(pa10_FORMS
    ${CMAKE_CURRENT_LIST_DIR}/circuititemedit.ui
    ${CMAKE_CURRENT_LIST_DIR}/pax_prototype.ui
    ${CMAKE_CURRENT_LIST_DIR}/plotwindow.ui
    ${CMAKE_CURRENT_LIST_DIR}/settingsdialog.ui
    ${CMAKE_CURRENT_LIST_DIR}/solverparam.ui
    ${CMAKE_CURRENT_LIST_DIR}/variablechooser.ui
)

add_executable(PA10mini ${pa10_SOURCES} ${pa10_FORMS} ${QRCS})

message(CMAKE_CURRENT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR})

target_include_directories(PA10mini PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}"
    "${CMAKE_CURRENT_LIST_DIR}/manzhuk/fcttask"
    "${CMAKE_CURRENT_LIST_DIR}/manzhuk"
)

target_link_libraries(PA10mini PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::OpenGL
    qwt
)

if(WIN32)
    target_link_libraries(PA10mini PRIVATE dl manzhuk)
else()
    # TODO: Provide and link a prebuilt Manzhuk library on Linux.
    target_link_libraries(PA10mini PRIVATE ${CMAKE_DL_LIBS})
endif()

# When shared third-party libraries are requested, place their runtime DLLs
# beside the executable so it can be launched from the build directory.
if(WIN32 AND BUILD_SHARED_LIBS)
    foreach(runtime_target IN ITEMS qwt dl)
        if(TARGET ${runtime_target})
            add_custom_command(TARGET PA10mini POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    "$<TARGET_FILE:${runtime_target}>"
                    "$<TARGET_FILE_DIR:PA10mini>"
                VERBATIM
            )
        endif()
    endforeach()
endif()
