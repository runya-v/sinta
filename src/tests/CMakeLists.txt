# Пример добавления теста:
# add_unit_tests(<Имя теста> <библиотека 1>  ... <библиотека N>)

include(${CMAKE_DIR}/UTest.cmake)

add_unit_test(ut_cpp11 base ${LOG_LIBS})
add_unit_test(ut_cpp_examples base ${LOG_LIBS})
add_unit_test(ut_stllibrary base chart ${LOG_LIBS})
add_unit_test(ut_welder base chart ${LOG_LIBS})
add_unit_test(ut_patterns_multi base chart ${LOG_LIBS})
