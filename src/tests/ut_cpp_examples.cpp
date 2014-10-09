#ifndef BOOST_STATIC_LINK
#   define BOOST_TEST_DYN_LINK
#endif // BOOST_STATIC_LINK

#define BOOST_TEST_MODULE CppExamples
#define BOOST_AUTO_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>

BOOST_AUTO_TEST_CASE(TestStlContainers1) {
    LOG_TO_STDOUT;
}


BOOST_AUTO_TEST_CASE(TestStlPtrs1) {
    LOG_TO_STDOUT;
}


BOOST_AUTO_TEST_CASE(TestStlAlgorithms1) {
    LOG_TO_STDOUT;
}
