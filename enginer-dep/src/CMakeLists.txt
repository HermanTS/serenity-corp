cmake_minimum_required (VERSION 3.6)

project (enginer-dep LANGUAGES CXX)

if(CMAKE_BUILD_TYPE MATCHES .*DEBUG*)
     set(TOOLS_PREFIX )
else()
     #set(TOOLS_PREFIX "x86_64-w64-mingw32-")
endif()


set(CMAKE_C_COMPILER "${TOOLS_PREFIX}gcc")
set(CMAKE_CXX_COMPILER "${TOOLS_PREFIX}g++")
set(CMAKE_LINKER "${TOOLS_PREFIX}ld")
set(CMAKE_OBJCOPY "${TOOLS_PREFIX}objcopy")


#set (CMAKE_CXX_FLAGS  "-O0  -std=gnu++11")

#set (CMAKE_CXX_FLAGS  "-Wall -std=gnu++11 -fext-numeric-literals")          

if(CMAKE_BUILD_TYPE MATCHES .*RELEASE*)
     set(CMAKE_CXX_FLAGS "-O0 -Wall -std=c++11 -fext-numeric-literals")# -static")
else()
     set(CMAKE_CXX_FLAGS "-O0 -std=c++11 -fext-numeric-literals")
endif()

set (SOURCES

    main-window.cpp
    window-widget.cpp
    
    Ship.cpp
    Unit.cpp
    main.cpp
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

target_link_libraries( ${PROJECT_NAME} gdiplus shlwapi ole32)# pthread)
