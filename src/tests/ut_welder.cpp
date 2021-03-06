#ifndef BOOST_STATIC_LINK
#   define BOOST_TEST_DYN_LINK
#endif // BOOST_STATIC_LINK

#define BOOST_TEST_MODULE Cpp11
#define BOOST_AUTO_TEST_MAIN

#include <memory>

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "Log.hpp"


static const char *WELDER_SETTINGS =
"{"
"\"amper:160\","
"\"ark_lenth:-5\"" // полярность - или +
"}";


enum class WelderJobs : uint8_t {
    MATERIAL,
    GAS,
    WIRE,
    WELDER_JOBS_NUMBER
};


enum class WelderParams : uint8_t {
    AMPERS,
    VOLTS,
    THICKNESS,
    FEED_SPEED,
    WELDER_PARAMS_NUMBER
};


enum class WeldingType : uint8_t {
    STANDART,
    IMPULSE,
    WELDING_TYPE_NUMBER
};


enum class WorkMode : uint8_t {
    TWO_TAKTS,
    FOUR_TAKTS,
    DOT,
    INTERVAL,
    WORK_MODE_NUMBER
};


enum class DynamikParams : uint8_t {
    DROSSEL,
    GAS_PURGE_TIME,
    DOT_WELDING_TIME,
    PAUSE_TIME,
    DYNAMIK_PARAMS_NUMBER
};


enum class WeldingMethods : uint8_t  {
    MMA,
    MG,
    TIG,
    WELDING_METHODS_NUMBER
};


namespace bptree = boost::property_tree;


class DeviceSencorer {
public:
    DeviceSencorer(const std::string &state_desc = WELDER_SETTINGS) {
        //bptree::ptree pt;
        //bptree::read_json(state_desc, pt);
        //uint32_t amper = pt.get<uint32_t>("amper");
        //int32_t ark_lenth = pt.get<int32_t>("ark_lenth");
        //LOG(DEBUG) << "amper=" << amper << "; ark_lenth=" << ark_lenth;
    }
};


class Idicator {
    class LedIndicator {
        enum class Leds : uint8_t {
            JOB_LIST,
            ACCIDENT,
            OVERHEATING,
            POSITIVE_POLARITY,
            NEGATIVE_POLARITY,
            AMPERS,
            VOLTS,
            THICKNESS,
            FEED_SPEED,
            STANDART_WELDING,
            IMPULSE_WELDING,
            TWO_TAKTS_WORK_MODE,
            FOUR_TAKTS_WORK_MODE,
            DOT_WORK_MODE,
            INTERVAL_WORK_MODE,
            DROSSEL_DYNAMIK_PARAMETER,
            GAS_PURGE_TIME_DYNAMIK_PARAMETER,
            DOT_WELDING_TIME_DYNAMIK_PARAMETER,
            PAUSE_TIME_DYNAMIK_PARAMETER,
            LEDS_NUMBER
        };

        std::vector<std::string> _names = {
            "JOB_LIST",
            "ERROR",
            "OVERHEATING",
            "POSITIVE_POLARITY",
            "NEGATIVE_POLARITY",
            "AMPERS",
            "VOLTS",
            "THICKNESS",
            "FEED_SPEED",
            "STANDART_WELDING",
            "IMPULSE_WELDING",
            "TWO_TAKTS_WORK_MODE",
            "FOUR_TAKTS_WORK_MODE",
            "DOT_WORK_MODE",
            "INTERVAL_WORK_MODE",
            "DROSSEL_DYNAMIK_PARAMETER",
            "GAS_PURGE_TIME_DYNAMIK_PARAMETER",
            "DOT_WELDING_TIME_DYNAMIK_PARAMETER",
            "PAUSE_TIME_DYNAMIK_PARAMETER"
        };

        LedIndicator() {
            //LOG(DEBUG) << _names[];
        }
    };

    class LcdIndicator {
    };
};


class GasController {
    std::weak_ptr<Idicator> _indicator;

public:
    GasController(const std::weak_ptr<Idicator> &indicator)
        : _indicator(indicator)
    {}
};


class WireFeeder {
    class MotorController {
        std::weak_ptr<Idicator> _indicator;
    public:
        MotorController(const std::weak_ptr<Idicator> &indicator)
            : _indicator(indicator)
        {}
    };

    class MotorBrake {
        std::weak_ptr<Idicator> _indicator;

    public:
        MotorBrake(const std::weak_ptr<Idicator> &indicator)
            : _indicator(indicator)
        {}
    };

    std::weak_ptr<Idicator> _indicator;

public:
    WireFeeder(const std::weak_ptr<Idicator> &indicator)
        : _indicator(indicator)
    {}


};


class Welder {
    std::shared_ptr<DeviceSencorer> _sencorer;
    std::shared_ptr<Idicator>       _indicator;
    std::shared_ptr<GasController>  _gas_ctrl;
    std::shared_ptr<WireFeeder>     _wire_feeder;

public:
    Welder() {
        LOG(DEBUG) << "init";
    }


};


BOOST_AUTO_TEST_CASE(TestWelder) {
    LOG_TO_STDOUT;

    Welder();
}
