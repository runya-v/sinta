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

#include "Policies.hpp"
#include "Chart.hpp"
#include "Demangle.hpp"

namespace ch = std::chrono;

static const std::size_t REPEAT_EACH_TEST = 10;


// trivial type with parametrized size
template<int N>
struct Trivial {
	std::size_t a;
	std::array<unsigned char, N-sizeof(a)> b;
	
	bool operator<(const Trivial &other) const {
		return a < other.a;
	}
};


template<>
struct Trivial<sizeof(std::size_t)> {
	std::size_t a;
	
	bool operator<(const Trivial &other) const {
		return a < other.a;
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
	std::size_t a = 0;

private:
	std::array<unsigned char, N-sizeof(a)> b;

public:
	NonTrivialArray(std::size_t a)
		: a(a)
	{}

	NonTrivialArray() = default;
	~NonTrivialArray() = default;

	bool operator<(const NonTrivialArray &other) const {
		return a < other.a;
	}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


template<class ...Types>
class Bench {
	typedef ch::milliseconds Mlsecs;
	typedef ch::microseconds Mcsecs;
	typedef ch::high_resolution_clock Clock;
	
	typedef Trivial<8>          TrivialSmall;         
	typedef Trivial<32>         TrivialMedium;        
	typedef Trivial<128>        TrivialLarge;         
	typedef Trivial<1024>       TrivialHuge;          
	typedef Trivial<4*1024>     TrivialMonster;       
	typedef NonTrivialArray<32> NonTrivialArrayMedium;

	std::unique_ptr<Chart> _chart;
	
	// variadic policy runner
	template<class Container>
	inline static void run(Container &, std::size_t) {
	}

	template<template<class> class Test, template<class> class ...Rest, class Container>
	inline static void run(Container &container, std::size_t size) {
		Test<Container>::run(container, size);
		run<Rest...>(container, size);
	}

	// benchmarking procedure
	template<class Container, class DurationUnit, template<class> class CreatePolicy, template<class> class ...TestPolicy>
	void bench(const std::string& type, const std::initializer_list<int> &sizes) {
		for (auto size : sizes) {
			Clock::duration duration;

			for (std::size_t i = 0; i < REPEAT_EACH_TEST; ++i) {
				auto container = CreatePolicy<Container>::make(size);
				Clock::time_point t0 = Clock::now();
				run<TestPolicy...>(container, size);
				Clock::time_point t1 = Clock::now();
				duration += t1 - t0;
			}
			_chart->newResult(type, std::to_string(size), ch::duration_cast<DurationUnit>(duration).count() / REPEAT_EACH_TEST);
		}
		CreatePolicy<Container>::clean();
	}


	template<template<class> class Benchmark>
	void types() {
		//Recursion end
	}


	template<template<class> class Benchmark, class T>
	void types() {
		Benchmark<T>::run();
		types<Benchmark, Types...>();
	}


	bool isTag(int c) {
		return std::isalnum(c) || c == '_';
	}


	std::string tag(std::string name) {
		std::replace_if(begin(name), end(name), [](char c){ return !is_tag(c); }, '_');
		std::string res;
		res.swap(name);
		return res;
	}


	template<typename T>
	void newDiagram(const std::string &testName, const std::string &unit) {
		_chart->newDiagram(
			tag(testName + " - " + demangle(typeid(T).name())), 
			title, 
			unit);
	}


	template<typename T>
	constexpr bool isTrivialOfSize(std::size_t size) {
		return std::is_trivial<T>::value && sizeof(T) == size;
	}


	template<typename T>
	constexpr bool isNonTrivialOfSize(std::size_t size) {
		return
			not std::is_trivial<T>::value &&
			sizeof(T) == size &&
			std::is_copy_constructible<T>::value &&
			std::is_copy_assignable<T>::value &&
			std::is_move_constructible<T>::value &&
			std::is_move_assignable<T>::value;
	}


	template<typename T>
	constexpr bool isNonTrivialNothrowMovable() {
		return
			not std::is_trivial<T>::value &&
			std::is_nothrow_move_constructible<T>::value &&
			std::is_nothrow_move_assignable<T>::value;
	}


	template<typename T>
	constexpr bool isNonTrivialNonNothrowMovable() {
		return
			not std::is_trivial<T>::value &&
			std::is_move_constructible<T>::value &&
			std::is_move_assignable<T>::value &&
			not std::is_nothrow_move_constructible<T>::value &&
			not std::is_nothrow_move_assignable<T>::value;
	}


	template<typename T>
	constexpr bool isNonTrivialNonMovable() {
		return
			not std::is_trivial<T>::value &&
			std::is_copy_constructible<T>::value &&
			std::is_copy_assignable<T>::value &&
			not std::is_move_constructible<T>::value &&
			not std::is_move_assignable<T>::value;
	}


	template<class T>
	constexpr bool isSmall() {
	   return sizeof(T) <= sizeof(std::size_t);
	}

	// Define all benchmarks
	template<class T>
	struct FillBack {
		static void run() {
			new_graph<T>("fill_back", "us");
			auto sizes = {100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000};
			bench<std::vector<T>, microseconds, Empty, FillBack>("vector", sizes);
			bench<std::list<T>,   microseconds, Empty, FillBack>("list",   sizes);
			bench<std::deque<T>,  microseconds, Empty, FillBack>("deque",  sizes);
			bench<std::vector<T>, microseconds, Empty, ReserveSize, FillBack>("vector_reserve", sizes);
			bench<std::vector<T>, microseconds, Empty, FillBackInserter>("vector_inserter", sizes);
			bench<std::list<T>,   microseconds, Empty, FillBackInserter>("list_inserter",   sizes);
			bench<std::deque<T>,  microseconds, Empty, FillBackInserter>("deque_inserter",  sizes);
		}
	};


	template<class T>
	struct EmplaceBack {
		static void run() {
			new_graph<T>("emplace_back", "us");
			auto sizes = {100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000};
			bench<std::vector<T>, microseconds, Empty, EmplaceBack>("vector", sizes);
			bench<std::list<T>,   microseconds, Empty, EmplaceBack>("list",   sizes);
			bench<std::deque<T>,  microseconds, Empty, EmplaceBack>("deque",  sizes);
		}
	};


	template<class T>
	struct FillFront {
		static void run() {
			new_graph<T>("fill_front", "us");
			auto sizes = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};

			// it is too slow with bigger data types
			if(is_small<T>()) {
				bench<std::vector<T>, microseconds, Empty, FillFront>("vector", sizes);
			}
			bench<std::list<T>,   microseconds, Empty, FillFront>("list",   sizes);
			bench<std::deque<T>,  microseconds, Empty, FillFront>("deque",  sizes);
		}
	};


	template<class T>
	struct EmplaceFront {
		static void run() {
			new_graph<T>("emplace_front", "us");
			auto sizes = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};

			// it is too slow with bigger data types
			if(is_small<T>()) {
				bench<std::vector<T>, microseconds, Empty, EmplaceFront>("vector", sizes);
			}
			bench<std::list<T>,   microseconds, Empty, EmplaceFront>("list",   sizes);
			bench<std::deque<T>,  microseconds, Empty, EmplaceFront>("deque",  sizes);
		}
	};


	template<class T>
	struct LinearSearch {
		static void run() {
			new_graph<T>("linear_search", "us");
			auto sizes = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
			bench<std::vector<T>, microseconds, FilledRandom, Find>("vector", sizes);
			bench<std::list<T>,   microseconds, FilledRandom, Find>("list",   sizes);
			bench<std::deque<T>,  microseconds, FilledRandom, Find>("deque",  sizes);
		}
	};


	template<class T>
	struct RandomInsert {
		static void run() {
			new_graph<T>("random_insert", "ms");
			auto sizes = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
			bench<std::vector<T>, milliseconds, FilledRandom, Insert>("vector", sizes);
			bench<std::list<T>,   milliseconds, FilledRandom, Insert>("list",   sizes);
			bench<std::deque<T>,  milliseconds, FilledRandom, Insert>("deque",  sizes);
		}
	};


	template<class T>
	struct RandomRemove {
		static void run() {
			new_graph<T>("random_remove", "ms");
			auto sizes = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
			bench<std::vector<T>, milliseconds, FilledRandom, Erase>("vector", sizes);
			bench<std::list<T>,   milliseconds, FilledRandom, Erase>("list",   sizes);
			bench<std::deque<T>,  milliseconds, FilledRandom, Erase>("deque",  sizes);
			bench<std::vector<T>, milliseconds, FilledRandom, RemoveErase>("vector_rem", sizes);
		}
	};

	template<class T>
	struct Sort {
		static void run() {
			new_graph<T>("sort", "ms");
			auto sizes = {100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000};
			bench<std::vector<T>, milliseconds, FilledRandom, Sort>("vector", sizes);
			bench<std::list<T>,   milliseconds, FilledRandom, Sort>("list",   sizes);
			bench<std::deque<T>,  milliseconds, FilledRandom, Sort>("deque",  sizes);
		}
	};


	template<class T>
	struct Destruction {
		static void run() {
			new_graph<T>("destruction", "us");
			auto sizes = {100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000};
			bench<std::vector<T>, microseconds, SmartFilled, SmartDelete>("vector", sizes);
			bench<std::list<T>,   microseconds, SmartFilled, SmartDelete>("list",   sizes);
			bench<std::deque<T>,  microseconds, SmartFilled, SmartDelete>("deque",  sizes);
		}
	};


	template<class T>
	struct NumberCrunching {
		static void run() {
			new_graph<T>("number_crunching", "ms");
			auto sizes = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};
			bench<std::vector<T>, milliseconds, Empty, RandomSortedInsert>("vector", sizes);
			bench<std::list<T>,   milliseconds, Empty, RandomSortedInsert>("list",   sizes);
			bench<std::deque<T>,  milliseconds, Empty, RandomSortedInsert>("deque",  sizes);
		}
	};

public:
	void Bench(const std::string &file_name) 
		: _chart(std::make_unique<Chart>(file_name))
	{
		BenchTypes<FillBack,     Types...>();
		BenchTypes<EmplaceBack,  Types...>();
		BenchTypes<FillFront,    Types...>();
		BenchTypes<EmplaceFront, Types...>();
		BenchTypes<LinearSearch, Types...>();
		BenchTypes<RandomInsert, Types...>();
		BenchTypes<RandomRemove, Types...>();
		BenchTypes<Sort,         Types...>();
		BenchTypes<Destruction,  Types...>();

		// it is really slow so run only for limited set of data
		BenchTypes<NumberCrunching, TrivialSmall, TrivialMedium>();
	}
};

