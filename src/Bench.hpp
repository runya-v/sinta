#include <random>
#include <array>
#include <vector>
#include <list>
#include <algorithm>
#include <deque>
#include <thread>
#include <iostream>
#include <cstdint>
#include <typeinfo>
#include <memory>
#include <chrono>
#include <utility>

#include "Policies.hpp"
#include "Chart.hpp"
#include "Demangle.hpp"

namespace ch = std::chrono;

static const std::size_t REPEAT_EACH_TEST = 10;


// trivial type with parametrized size
template<int N>
struct Trivial {
    std::size_t _a;
    std::array<unsigned char, N - sizeof(_a)> _b;

    bool operator<(const Trivial &other) const {
        return _a < other._a;
    }
};


template<>
struct Trivial<sizeof(std::size_t)> {
    std::size_t _a;

    bool operator<(const Trivial &other) const {
        return _a < other._a;
    }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// non trivial, quite expensive to copy but easy to move (noexcept not set)
class NonTrivialStringMovable {
    std::string data{"some pretty long string to make sure it is not optimized with SSO"};

public:
    std::size_t _a{0};

    NonTrivialStringMovable(std::size_t a)
        : _a(a)
    {}

    NonTrivialStringMovable() = default;
    ~NonTrivialStringMovable() = default;

    bool operator< (const NonTrivialStringMovable &other) const {
        return _a < other._a;
    }
};


// non trivial, quite expensive to copy but easy to move (with noexcept)
class NonTrivialStringMovableNoExcept {
    std::string data{"some pretty long string to make sure it is not optimized with SSO"};

public:
    std::size_t _a{0};

    NonTrivialStringMovableNoExcept(std::size_t a)
        : _a(a)
    {}

    NonTrivialStringMovableNoExcept(const NonTrivialStringMovableNoExcept &) = default;
    NonTrivialStringMovableNoExcept(NonTrivialStringMovableNoExcept &&) noexcept = default;
    NonTrivialStringMovableNoExcept() = default;
    ~NonTrivialStringMovableNoExcept() = default;

    NonTrivialStringMovableNoExcept &operator= (const NonTrivialStringMovableNoExcept &) = default;

    NonTrivialStringMovableNoExcept &operator= (NonTrivialStringMovableNoExcept &&other) noexcept {
        std::swap(data, other.data);
        std::swap(_a, other._a);
        return *this;
    }

    bool operator< (const NonTrivialStringMovableNoExcept &other) const {
        return _a < other._a;
    }
};


// non trivial, quite expensive to copy and move
template<int N>
class NonTrivialArray {
public:
    std::size_t _a = 0;

private:
    std::array<unsigned char, N - sizeof(_a)> _b;

public:
    NonTrivialArray(std::size_t a)
        : _a(a)
    {}

    NonTrivialArray() = default;
    ~NonTrivialArray() = default;

    bool operator<(const NonTrivialArray &other) const {
        return _a < other._a;
    }
};


template<class T>
struct TypeCheck {
    static constexpr bool isTrivialOfSize(std::size_t size) {
        return std::is_trivial<T>::value && sizeof(T) == size;
    }

    static constexpr bool isNonTrivialOfSize(std::size_t size) {
        return
            not std::is_trivial<T>::value &&
            sizeof(T) == size &&
            std::is_copy_constructible<T>::value &&
            std::is_copy_assignable<T>::value &&
            std::is_move_constructible<T>::value &&
            std::is_move_assignable<T>::value;
    }

    static constexpr bool isNonTrivialNothrowMovable() {
        return
            not std::is_trivial<T>::value &&
            std::is_nothrow_move_constructible<T>::value &&
            std::is_nothrow_move_assignable<T>::value;
    }

    static constexpr bool isNonTrivialNonNothrowMovable() {
        return
            not std::is_trivial<T>::value &&
            std::is_move_constructible<T>::value &&
            std::is_move_assignable<T>::value &&
            not std::is_nothrow_move_constructible<T>::value &&
            not std::is_nothrow_move_assignable<T>::value;
    }

    static constexpr bool isNonTrivialNonMovable() {
        return
            not std::is_trivial<T>::value &&
            std::is_copy_constructible<T>::value &&
            std::is_copy_assignable<T>::value &&
            not std::is_move_constructible<T>::value &&
            not std::is_move_assignable<T>::value;
    }

    static constexpr bool isSmall() {
        return sizeof(T) <= sizeof(std::size_t);
    }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


typedef Trivial<8>          TrivialSmall;
typedef Trivial<32>         TrivialMedium;
typedef Trivial<128>        TrivialLarge;
typedef Trivial<1024>       TrivialHuge;
typedef Trivial<4*1024>     TrivialMonster;
typedef NonTrivialArray<32> NonTrivialArrayMedium;


template<class ...Types>
class Bench {
    typedef ch::milliseconds Mlsecs;
    typedef ch::microseconds Mcsecs;
    typedef ch::high_resolution_clock Clock;

    template<typename T>
    class NewDiagram {
        bool isTag(int c) {
            return std::isalnum(c) || c == '_';
        }

        std::string tag(std::string name) {
            std::replace_if(begin(name), end(name), [this](char c){ return !isTag(c); }, '_');
            std::string res;
            res.swap(name);
            return res;
        }

    public:
        NewDiagram(Chart *chart, const std::string &testName, const std::string &unit) {
            std::string title = testName + " - " + std::string(Demangle(typeid(T).name()));
            chart->newDiagram(tag(title), title, unit);
        }
    };

    template<
        class Container,
        class DurationUnit,
        template<class> class CreatePolicy,
        template<class> class ...TestPolicies>
    struct BenchProcess {
        template<class ContainerType>
        static void run(Chart*, ContainerType&, std::size_t)
        {}

        template<template<class> class TestPolicy, template<class> class ...Rest, class ContainerType>
        static void run(Chart *chart, ContainerType &container, std::size_t size) {
            TestPolicy<ContainerType>::run(container, size);
            run<Rest...>(chart, container, size);
        }

        BenchProcess(Chart *chart, const std::string &type, const std::initializer_list<int> &sizes) {
            for (auto size : sizes) {
                Clock::duration duration;

                for (std::size_t i = 0; i < REPEAT_EACH_TEST; ++i) {
                    auto container = CreatePolicy<Container>::make(size);
                    Clock::time_point t0 = Clock::now();
                    run<TestPolicies...>(chart, container, size);
                    Clock::time_point t1 = Clock::now();
                    duration += t1 - t0;
                }
                chart->newResult(type, std::to_string(size), ch::duration_cast<DurationUnit>(duration).count() / REPEAT_EACH_TEST);
            }
            CreatePolicy<Container>::clean();
        }
    };

    template<class T>
    struct BenchFillBack {
        static void run(Chart *chart) {
            NewDiagram<T>(chart, "fill_back", "us");
            auto sizes = {100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000};
            BenchProcess<std::vector<T>, Mcsecs, Empty, FillBack>(chart, "vector", sizes);
            BenchProcess<std::list<T>,   Mcsecs, Empty, FillBack>(chart, "list",   sizes);
            BenchProcess<std::deque<T>,  Mcsecs, Empty, FillBack>(chart, "deque",  sizes);
            BenchProcess<std::vector<T>, Mcsecs, Empty, ReserveSize, FillBack>(chart, "vector_reserve", sizes);
            BenchProcess<std::vector<T>, Mcsecs, Empty, FillBackInserter>(chart, "vector_inserter", sizes);
            BenchProcess<std::list<T>,   Mcsecs, Empty, FillBackInserter>(chart, "list_inserter",   sizes);
            BenchProcess<std::deque<T>,  Mcsecs, Empty, FillBackInserter>(chart, "deque_inserter",  sizes);
        }
    };

    template<class T>
    struct BenchEmplaceBack {
        static void run(Chart *chart) {
            NewDiagram<T>(chart, "emplace_back", "us");
            auto sizes = {100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000};
            BenchProcess<std::vector<T>, Mcsecs, Empty, EmplaceBack>(chart, "vector", sizes);
            BenchProcess<std::list<T>,   Mcsecs, Empty, EmplaceBack>(chart, "list",   sizes);
            BenchProcess<std::deque<T>,  Mcsecs, Empty, EmplaceBack>(chart, "deque",  sizes);
        }
    };

    template<class T>
    struct BenchFillFront {
        static void run(Chart *chart) {
            NewDiagram<T>(chart, "fill_front", "us");
            auto sizes = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
            if(TypeCheck<T>::isSmall()) {
                BenchProcess<std::vector<T>, Mcsecs, Empty, FillFront>(chart, "vector", sizes);
            }
            BenchProcess<std::list<T>,  Mcsecs, Empty, FillFront>(chart, "list",   sizes);
            BenchProcess<std::deque<T>, Mcsecs, Empty, FillFront>(chart, "deque",  sizes);
        }
    };

    template<class T>
    struct BenchEmplaceFront {
        static void run(Chart *chart) {
            NewDiagram<T>(chart, "emplace_front", "us");
            auto sizes = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
            if (TypeCheck<T>::isSmall()) {
                BenchProcess<std::vector<T>, Mcsecs, Empty, EmplaceFront>(chart, "vector", sizes);
            }
            BenchProcess<std::list<T>,  Mcsecs, Empty, EmplaceFront>(chart, "list",   sizes);
            BenchProcess<std::deque<T>, Mcsecs, Empty, EmplaceFront>(chart, "deque",  sizes);
        }
    };

    template<class T>
    struct BenchLinearSearch {
        static void run(Chart *chart) {
            NewDiagram<T>(chart, "linear_search", "us");
            auto sizes = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
            BenchProcess<std::vector<T>, Mcsecs, FilledRandom, Find>(chart, "vector", sizes);
            BenchProcess<std::list<T>,   Mcsecs, FilledRandom, Find>(chart, "list",   sizes);
            BenchProcess<std::deque<T>,  Mcsecs, FilledRandom, Find>(chart, "deque",  sizes);
        }
    };

    template<class T>
    struct BenchRandomInsert {
        static void run(Chart *chart) {
            NewDiagram<T>(chart, "random_insert", "ms");
            auto sizes = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
            BenchProcess<std::vector<T>, Mlsecs, FilledRandom, Insert>(chart, "vector", sizes);
            BenchProcess<std::list<T>,   Mlsecs, FilledRandom, Insert>(chart, "list",   sizes);
            BenchProcess<std::deque<T>,  Mlsecs, FilledRandom, Insert>(chart, "deque",  sizes);
        }
    };

    template<class T>
    struct BenchRandomRemove {
        static void run(Chart *chart) {
            NewDiagram<T>(chart, "random_remove", "ms");
            auto sizes = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
            BenchProcess<std::vector<T>, Mlsecs, FilledRandom, Erase>(chart, "vector", sizes);
            BenchProcess<std::list<T>,   Mlsecs, FilledRandom, Erase>(chart, "list",   sizes);
            BenchProcess<std::deque<T>,  Mlsecs, FilledRandom, Erase>(chart, "deque",  sizes);
            BenchProcess<std::vector<T>, Mlsecs, FilledRandom, RemoveErase>(chart, "vector_rem", sizes);
        }
    };

    template<class T>
    struct BenchSort {
        static void run(Chart *chart) {
            NewDiagram<T>(chart, "sort", "ms");
            auto sizes = {100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000};
            BenchProcess<std::vector<T>, Mlsecs, FilledRandom, Sort>(chart, "vector", sizes);
            BenchProcess<std::list<T>,   Mlsecs, FilledRandom, Sort>(chart, "list",   sizes);
            BenchProcess<std::deque<T>,  Mlsecs, FilledRandom, Sort>(chart, "deque",  sizes);
        }
    };

    template<class T>
    struct BenchDestruction {
        static void run(Chart *chart) {
            NewDiagram<T>(chart, "destruction", "us");
            auto sizes = {100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000};
            BenchProcess<std::vector<T>, Mcsecs, SmartFilled, SmartDelete>(chart, "vector", sizes);
            BenchProcess<std::list<T>,   Mcsecs, SmartFilled, SmartDelete>(chart, "list",   sizes);
            BenchProcess<std::deque<T>,  Mcsecs, SmartFilled, SmartDelete>(chart, "deque",  sizes);
        }
    };

    template<class T>
    struct BenchNumberCrunching {
        static void run(Chart *chart) {
            NewDiagram<T>(chart, "number_crunching", "ms");
            auto sizes = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
            BenchProcess<std::vector<T>, Mlsecs, Empty, RandomSortedInsert>(chart, "vector", sizes);
            BenchProcess<std::list<T>,   Mlsecs, Empty, RandomSortedInsert>(chart, "list",   sizes);
            BenchProcess<std::deque<T>,  Mlsecs, Empty, RandomSortedInsert>(chart, "deque",  sizes);
        }
    };

    std::shared_ptr<Chart> _chart;

    template<template<class> class Benchmark>
    void types()
    {}

    template<template<class> class Benchmark, class T, typename ...Ts>
    void types() {
        Benchmark<T>::run(_chart.get());
        types<Benchmark, Ts...>();
    }

public:
    Bench(const std::string &file_name)
        : _chart(std::make_shared<Chart>(file_name))
    {
        types<BenchFillBack,     Types...>();
        types<BenchEmplaceBack,  Types...>();
        types<BenchFillFront,    Types...>();
        types<BenchEmplaceFront, Types...>();
        types<BenchLinearSearch, Types...>();
        types<BenchRandomInsert, Types...>();
        types<BenchRandomRemove, Types...>();
        types<BenchSort,         Types...>();
        types<BenchDestruction,  Types...>();

        // it is really slow so run only for limited set of data
        types<BenchNumberCrunching, TrivialSmall, TrivialMedium>();
    }
};
