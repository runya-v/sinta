#ifndef BOOST_STATIC_LINK
#   define BOOST_TEST_DYN_LINK
#endif // BOOST_STATIC_LINK

#define BOOST_TEST_MODULE Cpp11
#define BOOST_AUTO_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>

#include <vector>
#include <sstream>

#include "Log.hpp"

class MovTest {
    class Mov {
    public:
        int _value;

        Mov()
        {
            LOG(TEST);
        }

        Mov (Mov &&m)
            : _value(m._value)
        {
            LOG(TEST) << "value=" << _value;
        }

        Mov& operator= (Mov &&m) {
            if (&_value != &m._value) {
                LOG(TEST) << std::hex << (&_value) << " != " << (&m._value);
                _value = m._value;
            }
            else {
                LOG(TEST) << std::hex << (&_value) << " == " << (&m._value);
            }
            return *this;
        }
    };
public:
    MovTest() {
        Mov m1;
        m1._value = 10;
        Mov m2((Mov&&)m1);
        m1 = (Mov&&)m2;
        m1 = (Mov&&)m1;
    }
};


constexpr int GiveFive() {
    //LOG(TEST);
    return 5;
}

class Constexpt {
    //constexpr static double acceleration_of_gravity = 9.8;
    //constexpr static double moon_gravity = acceleration_of_gravity / 6;

public:
    Constexpt() {
        constexpr double acceleration_of_gravity = 9.8;
        constexpr double moon_gravity = acceleration_of_gravity / 6;

        uint8_t some_value[GiveFive() + 7];
        LOG(TEST) << "sizeof some_value = " << sizeof(some_value);
        LOG(TEST) << "acceleration_of_gravity = " << acceleration_of_gravity;
        LOG(TEST) << "moon_gravity = " << moon_gravity;
    }
};


// template class std::vector<MyClass>;  // Инстанциирование в данной точке
// extern template class std::vector<MyClass>; // Запрет инстанциирования в данной единице трансляции


class InitialiserList {
    std::string get_line(std::vector<int> &&v) {
        std::stringstream ss;
        ss << "{";
        for (int &i : v) {
            ss << i << ",";
        }
        ss << "}";
        return ss.str();
    }

public:
    InitialiserList(std::initializer_list<int> list) {
        std::vector<int> v1(list);
        LOG(TEST) << "list: " << get_line((std::vector<int>&&)v1);
        std::vector<int> v2{1, 2, 3, 4};
        LOG(TEST) << "v{}: " <<  get_line((std::vector<int>&&)v2);
        std::vector<int> v3 = {5, 6, 7, 8};
        LOG(TEST) << "v=: " << get_line((std::vector<int>&&)v3);
    }
};


class UniversalInitialiser {
    struct BasicStruct {
        int _x;
        double _y;
    };

    struct AltStruct {
        int _x;
        double _y;

        AltStruct(int x, double y)
            : _x(x), _y(y)
        {}
    };

public:
    UniversalInitialiser() {
        BasicStruct v1{5, 3.2};
        LOG(TEST) << "BasicStruct: {" << v1._x << "," << v1._y << "}";
        AltStruct v2{2, 4.3};
        LOG(TEST) << "AltStruct: {" << v2._x << "," << v2._y << "}";
    }
};


class LambdaFunction {
    std::string get_str() {
        return "test string";
    }

public:
    LambdaFunction() {
        auto f1 = [](int x, int y) { return x + y; };
        auto f2 = [](int x, int y)->float { return x + y; };
        LOG(TEST) << f1(1, 2) << "; " << f2(3, 4);

        LOG(TEST) << [](int x, int y) { return x + y; } (5, 5);

        int total = 0;
        int value = 5;
        [&, value](int x) { total += (x * value); } (3);
        LOG(TEST) << total;

        LOG(TEST) << [=](int x)->int { return total + (x * value); } (1);

        LOG(TEST) << [this]()->std::string { return this->get_str(); } ();

        [this]() { LOG(TEST) << this->get_str(); } ();
    }
};


class FunctionAutoRetType {
    struct SomeStruct
    {
        auto funcName(int x, int y)->int {
            LOG(TEST);
            return x + y;
        }
    };

public:
    FunctionAutoRetType() {
        SomeStruct str;
        LOG(TEST) << str.funcName(6, 9);
    }
};


// struct Final fital {
//     virtual void func() final {};
// };


class NullPtr {
    void foo(char *) {
        LOG(TEST);
    }

    void foo(int) {
        LOG(TEST);
    }

    char *pc = nullptr;     // верно
    int  *pi = nullptr;     // верно
    bool   b = nullptr;     // верно. b = false.
    //int    i = nullptr;     // ошибка

public:
    NullPtr () {
        LOG(TEST);
        foo(nullptr);           // вызывает foo(char *), а не foo(int);
    }
};


class EnumTypes {
    enum class Enumeration {
        Val1,
        Val2,
        Val3 = 100,
        Val4, /* = 101 */
    };

    //enum Enum1;                   // неверно для C++ и C++11; низлежащий тип не может быть определён
    enum Enum2 : unsigned int;    // верно для C++11, низлежащий тип указан явно
    enum class Enum3;             // верно для C++11, низлежащий тип — int
    enum class Enum4 : unsigned int; // верно для C++11.
    //enum Enum2 : unsigned short;  // неверно для C++11, поскольку Enum2 ранее объявлен с иным низлежащим типом
};


class UsingType {
    template< typename First, typename Second, int third>
    class SomeType;
    struct OtherType;
    template< typename Second>
    using TypedefName = SomeType<OtherType, Second, 5>;

    typedef void (*OldStyle)(double);  // Старый стиль
    using NewStyle = void (*)(double); // Новый синтаксис
};


class UnionStyle {
    struct Point  {
        Point() {}
        Point(int x, int y): x_(x), y_(y) {}
        int x_, y_;
    };

    union U {
        int z;
        double w;
        Point p;  // Неверно для C++03, поскольку Point имеет нетривиальный конструктор.  Однако код работает корректно в C++11.
        U() { new( &p ) Point(); } // Для объединения не определяются нетривиальные методы.
                                   // При необходимости они могут быть удалены, чтобы работало ручное определение
    };
};


class VarargTemplates {
    std::stringstream _ss;

    void my_printf(const char *s)
    {
        LOG(TEST);

        while (*s) {
            if (*s == '%' && *(++s) != '%') {
                throw std::runtime_error("invalid format string: missing arguments");
            }
            _ss << *s++;
        }
    }

    template<class T, class... Args>
    void my_printf(const char *s, T value, Args... args)
    {
        const int size = sizeof...(Args);
        LOG(TEST) << "args size = " << size;

        while (*s) {
            if (*s == '%' && *(++s) != '%') {
                LOG(TEST) << value;
                _ss << value;
                ++s;
                my_printf(s, args...); // продолжаем обработку аргументов, даже если *s == 0
                return;
            }
            _ss << *s++;
        }
        throw std::logic_error("extra arguments provided to printf");
    }

public:
    VarargTemplates() {
        my_printf("test %d %d %d", 1, 2, 3);
        LOG(TEST) << _ss.str();
    }
};
////////////////////////////////////////////////////////////////////////////////////////////////////


BOOST_AUTO_TEST_CASE(TestCpp11) {
    LOG_TO_STDOUT;

    MovTest();
    Constexpt();
    InitialiserList({4, 3, 2, 1});
    UniversalInitialiser();
    LambdaFunction();
    FunctionAutoRetType();
    NullPtr();
    VarargTemplates();
}
