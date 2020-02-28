cmake_minimum_required (VERSION 3.6)

project (batle-sim)

if(DEFINED CMAKE_ECLIPSE_VERSION)
  #  set(GCC_LIB /lib/gcc/x86_64-pc-cygwin/7.4.0/)
    #set(SYS_INCLUDES /usr/include /usr/include/w32api ${GCC_LIB}/include  ${GCC_LIB}/include/c++)   
    message(INFO ${CMAKE_ECLIPSE_VERSION})
    #separate_arguments(SYS_INCLUDES UNIX_COMMAND ${SYS_INCLUDES_OUT}) # create a list
    #include_directories(SYSTEM ${SYS_INCLUDES} ) # add list to includes
endif()    
    

if(CMAKE_BUILD_TYPE MATCHES .*DEBUG*)
     set(TOOLS_PREFIX )
else()
     #set(TOOLS_PREFIX "x86_64-w64-mingw32-")
endif()


#set(CMAKE_C_COMPILER "${TOOLS_PREFIX}gcc")
#set(CMAKE_CXX_COMPILER "${TOOLS_PREFIX}g++")
#set(CMAKE_LINKER "${TOOLS_PREFIX}ld")
#set(CMAKE_OBJCOPY "${TOOLS_PREFIX}objcopy")

if(CMAKE_BUILD_TYPE MATCHES .*RELEASE*)
     set(CMAKE_CXX_FLAGS "-O0 -Wall -std=c++11 -fext-numeric-literals")# -static")
else()
     set(CMAKE_CXX_FLAGS "-O0 -std=c++11 -fext-numeric-literals")
endif()

set (COMMON_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../common-lib/)

set (SOURCES

    ${COMMON_LIB_PATH}/common/main-window.cpp
    ${COMMON_LIB_PATH}/common/window-widget.cpp

    main.cpp
    BattleField.cpp
    MenuWidget.cpp
   )

include_directories(
    ${COMMON_LIB_PATH}/nuklear_cross
    ${COMMON_LIB_PATH}/common
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_definitions(
    -DNKCD=NKC_GDIP
    #-DGLOBAL_KEY_EVENT_DEBUG
    )

add_executable(${PROJECT_NAME} ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
CXX_STANDART 11
CXX_STANDART_REQUIRED YES
CXX_EXTENSIONS NO)

target_link_libraries( ${PROJECT_NAME} gdiplus shlwapi ole32)
