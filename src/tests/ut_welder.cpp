#ifndef BOOST_STATIC_LINK
#   define BOOST_TEST_DYN_LINK
#endif // BOOST_STATIC_LINK

#define BOOST_TEST_MODULE Cpp11
#define BOOST_AUTO_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>

#include "Log.hpp"


enum class WelderJobs {
    MATERIAL,
    GAS,
    WIRE
};


enum class WelderParams {
    AMPERS,
    VOLTS,
    THICKNESS,
    FEED_SPEED
};


enum class WeldingType {
    STANDART,
    IMPULSE
};


enum class WorkMode {
    TWO_TAKTS,
    FOUR_TAKTS,
    DOT,
    INTERVAL
};

BOOST_AUTO_TEST_CASE(TestWelder) {
    LOG_TO_STDOUT;
}
