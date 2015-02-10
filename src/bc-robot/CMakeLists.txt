set(APP_LIB bc_robot)
add_library(${APP_LIB}
    GetHistory.cpp
    MongoProcessor.cpp
    )


set(APP_BIN bc-robot)
add_executable(${APP_BIN}
    main.cpp
    )
target_link_libraries(${APP_BIN}
    ${APP_LIB}
    templating
    ctpp2
    base
    pthread
    ${Boost_THREAD_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    ${Boost_IOSTREAMS_LIBRARY}
    ${Boost_DATE_TIME_LIBRARY}
    )

#if(ENABLE_TESTS)
#    add_unit_test(ut_ctpp_html base http_server templating ctpp2 ${LOG_LIBS})
#    add_unit_test(ut_ctpp_file_load base http_server templating ctpp2 ${LOG_LIBS})
#endif(ENABLE_TESTS)

