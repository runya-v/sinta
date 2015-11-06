# Пример добавления теста:
# add_unit_tests(<Имя теста> <библиотека 1>  ... <библиотека N>)

include(${CMAKE_DIR}/UTest.cmake)

add_unit_test(ut_cpp11 log ${LOG_LIBS})
add_unit_test(ut_cpp_examples log ${LOG_LIBS})
add_unit_test(ut_welder log chart ${LOG_LIBS})
add_unit_test(ut_patterns_multi log chart ${LOG_LIBS})
add_unit_test(ut_sort_algorithms log ${LOG_LIBS})
