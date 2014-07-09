set(APP_LIB web_client)
add_library(${APP_LIB}
	WebViewHandler.cpp
	WebView.cpp
    )


set(APP_BIN web-client)
add_executable(${APP_BIN}
    main.cpp
    )
target_link_libraries(${APP_BIN}
    ${APP_LIB}
    cef_dll_wrapper
    cef
    ${GTK3_LIBRARIES}
    base
    pthread
    ${Boost_THREAD_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    ${Boost_IOSTREAMS_LIBRARY}
    ${Boost_DATE_TIME_LIBRARY}
    )
