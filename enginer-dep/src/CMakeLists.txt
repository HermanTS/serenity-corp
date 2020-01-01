cmake_minimum_required (VERSION 3.6)

project (enginer-dep)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_LINKER "ld")
set(CMAKE_OBJCOPY "objcopy")


set (CMAKE_CXX_FLAGS  "-O0  -Wall -std=c++11")
            


set (SOURCES
    main.cpp
    main-window.cpp
    window-widget.cpp
   )

set (COMMON_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../common-lib/)

include_directories(
    ${COMMON_LIB_PATH}/nuklear_cross
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_definitions(
    -DNKCD=NKC_GDIP
    )

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries( ${PROJECT_NAME} gdiplus shlwapi ole32 pthread)