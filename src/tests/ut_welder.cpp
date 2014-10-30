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


enum class DynamikParams {
    DROSSEL,
    GAS_PURGE_TIME,
    DOT_WELDING_TIME,
    PAUSE_TIME
};


enum class WeldingMethods {
	MMA,
	MG,
	TIG
};


class Idicator {
	class LedIndicator {
	};
	
	class LcdIndicator {
	};
};


class GasController {
};


class WireFeeder {
};


class Welder {
	WelderJobs     _job;
	WelderParams   _param;
	WeldingType    _type;
	WorkMode       _mode;
	DynamikParams  _dynamik_param;
	WeldingMethods _method;
	
	Idicator _indicator;
	GasController _gas_ctrl;
	WireFeeder _wire_feeder;
	
public:
	Welder() {
		LOG(DEBUG);
	}
	
	void init() {
	}
	
	
};


BOOST_AUTO_TEST_CASE(TestWelder) {
    LOG_TO_STDOUT;
}
