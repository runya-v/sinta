include_directories("${HTTP_SERVER_TEMPLATING_DIR}")
set(TMPLT_LIB templating)
add_library(${TMPLT_LIB}
    Compiler.cpp
    utility.cpp
    Generator.cpp
    TextFileLoader.cpp
    )

