# Пример добавления теста:
# add_unit_tests(<Имя теста> <библиотека 1>  ... <библиотека N>)

#add_unit_test(ut_ctpp_gen_html base ${LOG_LIBS})
add_unit_test(ut_cpp11 base ${LOG_LIBS})
add_unit_test(ut_stllibrary base ${LOG_LIBS})
