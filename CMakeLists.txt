cmake_minimum_required(VERSION 2.8)

message("\nConfigure project Run...")

project(Run)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING
        "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
        FORCE
        )
endif()


# Общие флаги для всех сборок.
add_definitions(
    -pedantic -pedantic-errors
    -std=gnu++11
    -pipe -fPIC
    -Wall -Wno-long-long -Wno-inline
    -finline-functions -finline-limit=2000
    --param large-function-growth=5000 --param inline-unit-growth=600
    -D__STDC_LIMIT_MACROS=1 -I.
    -D_GLIBCXX_USE_NANOSLEEP
    -DDLL_PUBLIC=__attribute__\(\(visibility\(\"default\"\)\)\)
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
set(SRC_DIR    ${ROOT_DIR}/src)
set(EXT_DIR    ${ROOT_DIR}/ext)
set(BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINARY_DIR}/${CMAKE_BUILD_TYPE}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BINARY_DIR}/${CMAKE_BUILD_TYPE}/lib)

add_definitions(-DSRC_DIR="${SRC_DIR}")


# Указание общих настроек
link_directories("/usr/lib")
link_directories("/usr/local/lib")


# Установка общих директорий включаемых файлов
include_directories(${SRC_DIR})


# Настройка опций сборки компонент
OPTION(ENABLE_TESTS "Enable TESTS support [default: ON]" ON)
OPTION(ENABLE_CTPP2 "Enable CTPP2 support [default: ON]" ON)
OPTION(ENABLE_CEF3  "Enable CEF3 support [default: ON]"  OFF)
OPTION(ENABLE_WELDER_MODEL_WEB  "Enable Welder model [default: ON]"  OFF)


# Поиск библиотек Boost версии старше 1.48
find_package(Boost 1.48 COMPONENTS
    date_time
    filesystem
    program_options
    system
    signals
    regex
    thread
    random
    unit_test_framework
    iostreams
    serialization
    )

if(Boost_FOUND)
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_USE_STATIC_LIBS OFF)
    set(Boost_USE_STATIC_RUNTIME OFF)
    set(BOOST_ALL_DYN_LINK ON)

    message(STATUS "Boost_LIBRARY_DIRS: \"${Boost_LIBRARY_DIRS}\"")
    message(STATUS "Boost_INCLUDE_DIRS: \"${Boost_INCLUDE_DIRS}\"")
    message(STATUS "Boost_LIBRARIES:")
    foreach(BOOST_LIB ${Boost_LIBRARIES})
        message(STATUS "    \"${BOOST_LIB}\"")
    endforeach()

    link_directories(${Boost_LIBRARY_DIRS})
    include_directories(${Boost_INCLUDE_DIRS})

    add_definitions(-DBOOST_DIN_LINK)
else()
    message(FATAL_ERROR "Boost libraries not found. Please get a copy from http://www.boost.org")
endif()


# Поиск дополнительных библиотек
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}")
include(TakeComponent)


# Включение в сборку компонент
# Директорию test включается только, если определен макро ENABLE_TESTS=ON
add_subdirectory("${SRC_DIR}")

set(LOG_LIBS z ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY} ${Boost_DATE_TIME_LIBRARY} ${Boost_IOSTREAMS_LIBRARY})


if(ENABLE_TESTS)
    set(ALL_TESTS ON)

    string( TOLOWER ${ENABLE_TESTS} LOWER_STR)
    if (NOT ${LOWER_STR} MATCHES "on" AND NOT ${LOWER_STR} MATCHES "all")
        set(ALL_TESTS OFF)
        separate_arguments(LOWER_STR)
        foreach (TEST_NAME ${LOWER_STR})
            message(STATUS "Enable test: `${TEST_NAME}`")
            set(ut_${TEST_NAME} ON)
        endforeach()
    else()
        message(STATUS "Enable ALL tests")
    endif()
    # Поиск конкретного указанного теста, в противном случае будут добавлены все тесты
    #get_cmake_property(VARIABLE_NAMES VARIABLES)
    #foreach (VAR_NAME ${VARIABLE_NAMES})
    #    if (VAR_NAME MATCHES "^TEST")
    #        message(STATUS "ALL_TESTS set to OFF; enable ${VAR_NAME}")
    #        set(ALL_TESTS OFF)
    #        set(TEST_${VAR_NAME} ON)
    #    else()
    #        message(STATUS "### ${VAR_NAME}")
    #    endif()
    #endforeach()

    enable_testing()

    include(UTest)

    # Инициализировать общие тесты
    #set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${TESTS_DIR})
    set(TESTS_DIR ${SRC_DIR}/tests)
    message(STATUS "TESTS_DIR: ${TESTS_DIR}")
    add_subdirectory("${TESTS_DIR}")
else(ENABLE_TESTS)
    message(STATUS "Directory tests is not included to build. Run cmake -DENABLE_TESTS=ON or -DENABLE_TESTS=\"ut_test_1 ut_test_2 ...\"to include.")
endif()

if(ENABLE_CTPP2)
    set(CTPP2_EXT_DIR "${EXT_DIR}/ctpp2")
    add_custom_target("build_ctpp2" ALL)
    add_custom_command(
        TARGET "build_ctpp2"
        WORKING_DIRECTORY "${CTPP2_EXT_DIR}"
        COMMAND "./build.sh"
        DEPENDS "ctpp2-2.8.3"
        )

    set(HTTP_SERVER_DIR "${SRC_DIR}/http-server")
    message(STATUS "Add dir: `${HTTP_SERVER_DIR}`")
    set(CTPP2_EXT_LIBS_DIR "${CTPP2_EXT_DIR}/ctpp2-2.8.3/bld")
    link_directories("${CTPP2_EXT_LIBS_DIR}")
    message(STATUS "CTPP2 libraries dir: `${CTPP2_EXT_LIBS_DIR}`")
    set(CTPP2_EXT_INCS_DIR "${CTPP2_EXT_DIR}/ctpp2-2.8.3/include")
    include_directories("${CTPP2_EXT_INCS_DIR}")
    message(STATUS "CTPP2 includes dir: `${CTPP2_EXT_INCS_DIR}`")

    add_subdirectory("${HTTP_SERVER_DIR}")
endif()

if(ENABLE_CEF3)
    #find_package(PkgConfig REQUIRED)
    #pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
    #include_directories(${GTK3_INCLUDE_DIRS})
    #link_directories(${GTK3_LIBRARY_DIRS})
    #add_definitions(${GTK3_CFLAGS_OTHER})
    #
    #find_library(
    #   UDEV_LIBRARIES
    #   NAMES "libudev.so.0"
    #   PATHS "/usr/lib" "/usr/local/lib" "/usr/lib/x86_64-linux-gnu"
    #   DOC "Path where the `libudev.so.0` libraries can be found"
    #   )
    #
    #if(NOT UDEV_LIBRARIES)
    #   message(FATAL_ERROR "ERROR: Cannot find `libudev.so.0`, try: `LIBUDEV=$(find /usr -name libudev\.so); sudo ln -s $LIBUDEV $LIBUDEV.0`, aborting")
    #endif()

    set(CEF3_EXT_DIR "${EXT_DIR}/cef3")
    add_custom_target("build_cef3" ALL)
    add_custom_command(
        TARGET "build_cef3"
        WORKING_DIRECTORY "${CEF3_EXT_DIR}"
        COMMAND "./build.sh"
        ARGS "${CMAKE_BUILD_TYPE}"
        DEPENDS "cef_binary_3.1750.1738_linux64"
        )

    set(WEB_CLIENT_APP_DIR "${SRC_DIR}/web-client-app")
    message(STATUS "Add dir: `${WEB_CLIENT_APP_DIR}`")

    set(CEF3_EXT_LIBS_DIR "${CEF3_EXT_DIR}/cef_binary_3.1750.1738_linux64/bld/${CMAKE_BUILD_TYPE}/lib")
    link_directories("${CEF3_EXT_LIBS_DIR}")
    message(STATUS "CEF3 libraries dir: `${CEF3_EXT_LIBS_DIR}`")

    set(CEF3_EXT_INCS_DIR "${CEF3_EXT_DIR}/cef_binary_3.1750.1738_linux64")
    set(CEF3_EXT_INCS_DIR "${CEF3_EXT_INCS_DIR}" "${CEF3_EXT_INCS_DIR}/include")
    include_directories("${CEF3_EXT_INCS_DIR}")
    message(STATUS "CEF3 includes dir: `${CEF3_EXT_INCS_DIR}`")

    add_subdirectory("${WEB_CLIENT_APP_DIR}")
endif()

if(ENABLE_WELDER_MODEL_WEB)
    take_component(WTCPP)
    set(WELDER_MODEL_WEB_DIR "${SRC_DIR}/welder-model-web")
    message(STATUS "Add dir: `${WELDER_MODEL_WEB_DIR}`")
    add_subdirectory("${WELDER_MODEL_WEB_DIR}")
endif()
