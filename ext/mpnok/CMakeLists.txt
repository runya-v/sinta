cmake_minimum_required(VERSION 2.8)

message("\nConfigure project MpNok...")

project(MpNok)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING
        "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
        FORCE
        )
endif()


# Общие флаги для всех сборок.
add_definitions(
    -pedantic -pedantic-errors
    -pthread -std=gnu++11
    -pipe -fPIC
    -Wall -Wno-long-long -Wno-inline
    -finline-functions -finline-limit=2000
    --param large-function-growth=5000 --param inline-unit-growth=600
    #-D__STDC_LIMIT_MACROS=1 -I.
    -D_GLIBCXX_USE_NANOSLEEP
    #-DDLL_PUBLIC=__attribute__\(\(visibility\(\"default\"\)\)\)
    )

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    #Добавление профилировки: для включения профилировки запускаем cmake -DGPROF=1.
    if(GPROF)
        add_definitions(-pg)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
    endif()

    #Добавляем флаги для построения отладочной инфомрации.
    add_definitions(-fno-inline-functions -fno-inline)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    add_definitions(-O3 -ggdb3)
endif()


# Установка вспомогательных констант
set(ROOT_DIR   ${CMAKE_CURRENT_SOURCE_DIR})
set(SRC_DIR    ${ROOT_DIR})
set(BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(LIB_DIR    ${BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIB_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB_DIR})

#set(CMAKE_STATIC_LINKER_FLAGS "Wl,-no-as-needed")
set(CMAKE_SHARED_LINKER_FLAGS "Wl,-no-as-needed")

add_definitions(-DSRC_DIR="${SRC_DIR}")

# Установка общих директорий включаемых файлов
include_directories(${SRC_DIR})

set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "-pthread")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "-pthread")

set(MPNOK_LIB "mp_nok")
add_library(${MPNOK_LIB} STATIC
    Log.cpp
    Task.cpp
    ThreadPool.cpp
    Nok.cpp
    NumberGenerator.cpp
    StdoutToStdin.cpp
    )
set(MPNOK "mp-nok")
add_executable(${MPNOK} main.cpp)
target_link_libraries(${MPNOK} ${MPNOK_LIB} "-Wl,-no-as-needed")
