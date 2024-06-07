cmake_minimum_required(VERSION 3.20)

project(GottvergessenLoader CXX ASM_MASM)

set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")

# Git commit embed
#include(scripts/git.cmake)

# Fetch modules
message("\nFetching modules")
include(scripts/g3log.cmake)
include(scripts/json.cmake)
include(scripts/cpr.cmake)
include(scripts/imgui.cmake)


# GottvergessenLoader
message(STATUS "GottvergessenLoader")
file(GLOB_RECURSE SRC_MAIN
    "${SRC_DIR}/**.hpp"
    "${SRC_DIR}/**.h"
    "${SRC_DIR}/**.cpp"
    "${SRC_DIR}/**.cc"
    "${SRC_DIR}/**.cxx"
    "${SRC_DIR}/**.asm"
)

if (MSVC)
  add_compile_options(/bigobj)
else ()
  add_compile_options(-Wa,-mbig-obj)
endif ()

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  enable_language("RC")
  set (ICON "${SRC_DIR}/gottvergessen_loader.rc")
endif()

add_executable(GottvergessenLoader ${SRC_MAIN} ${ICON})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(TARGET GottvergessenLoader PROPERTY CXX_STANDARD 23) # 23 Because std::format is not avalible in std:c++20 for some reason. Maybe it's because i use v142 toolset.

source_group(TREE ${SRC_DIR} PREFIX "src" FILES ${SRC_MAIN} )

target_include_directories(GottvergessenLoader PRIVATE 
    "${SRC_DIR}"
    "${json_SOURCE_DIR}/single_include"
    "${imgui_SOURCE_DIR}"
)

target_precompile_headers(GottvergessenLoader PRIVATE "${SRC_DIR}/common.hpp")
target_link_libraries(GottvergessenLoader PRIVATE g3log imgui cpr)

# Warnings as errors
set_property(TARGET GottvergessenLoader PROPERTY COMPILE_WARNING_AS_ERROR ON)

add_compile_definitions(GottvergessenLoader 
    "_CRT_SECURE_NO_WARNINGS"
    "NOMINMAX"
    "WIN32_LEAN_AND_MEAN"
    "_MBCS"
)
