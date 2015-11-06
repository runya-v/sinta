#ifndef BOOST_STATIC_LINK
#   define BOOST_TEST_DYN_LINK
#endif // BOOST_STATIC_LINK

#define BOOST_TEST_MODULE CppExamples
#define BOOST_AUTO_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>

#include <vector>
#include <array>
#include <cstdlib>
#include <ctime>
#include <map>
#include <string>
#include <cmath>
#include <ctime>
#include <climits>
#include <memory>
#include <functional>

#include "Log.hpp"


namespace sort {
namespace exchange {
/**
 * \brief Класс реализующий пузырьковую сортировку, относиться к множеству объменных сортировок.
 */
class BubbleSort {
public:
    /**
     * \brief Объменная сортировка выбором .
     *
     * \param buf Ссылка на буфер объектов, для которых определён оператор < и >
     */
    template<class T>
    BubbleSort(std::vector<T>& buf) {
        for (size_t m = buf.size() - 1; m > 1; --m) {
            for (size_t i = 0; i < m; i++) {
                T &a = &buf[i];
                T &b = &buf[i + 1];
                if (a > b) {
                    a ^= b;
                    b ^= a;
                    a ^= b;
                }
            }
        }
    }
};
} // exchange
} // sort


namespace test {
namespace details {
/// Количество тестируемых массивов в эксперименте
static const size_t ARRAYS_NUM = 10;

/// Минимальный размер тестируемого массива
static const size_t MIN_ARRAY_LEN = (1 << 6);

/// Максимальный размер тестируемого массива
static const size_t MAX_ARRAY_LEN = (1 << (ARRAYS_NUM + 6));


/**
 * \brief Класс сложного объекта для применения в качестве элемента сортируемого массива.
 */
class TestSortElement {
    std::string _str;

public:
    TestSortElement() {
        _str.resize(MIN_ARRAY_LEN);
        for (size_t i = 0; i < MIN_ARRAY_LEN; ++i) {
            size_t rnd = rand();
            if (rnd < static_cast<size_t>(std::floor(static_cast<double>(RAND_MAX) * 0.5 + 0.5))) {
                rnd = static_cast<size_t>('a') + rnd % (static_cast<size_t>('z') - static_cast<size_t>('a'));
            }
            else {
                rnd = static_cast<size_t>('A') + rnd % (static_cast<size_t>('Z') - static_cast<size_t>('A'));
            }
            _str[i] = static_cast<char>(rnd);
        }
    }

    TestSortElement(const TestSortElement& element) : _str(element._str)
    {}

    TestSortElement& operator = (const TestSortElement& element) {
        if (this not_eq &element) {
            _str = element._str;
        }
        return *this;
    }

    bool operator < (const TestSortElement& element) const {
        return (this == &element) ? false : (_str < element._str);
    }

    bool operator <= (const TestSortElement& element) const {
        return (this == &element) ? true : (_str <= element._str);
    }

    bool operator > (const TestSortElement& element) const {
        return (this == &element) ? false : (_str > element._str);
    }

    bool operator >= (const TestSortElement& element) const {
        return (this == &element) ? true : (_str >= element._str);
    }

    bool operator == (const TestSortElement& element) const {
        return (this == &element) ? true : (_str == element._str);
    }

    bool operator != (const TestSortElement& element) const {
        return (this not_eq &element) ? true : (_str not_eq element._str);
    }

    const std::string& string() const {
        return _str;
    }
};


/**
 * \brief Оператор вывода TestSortElement в стандартный вывод.
 */
std::ostream& operator << (std::ostream& stream, const TestSortElement &element) {
    stream << element.string();
    return stream;
}


/**
 * \brief Метод возвращающий произвольный элемент для тривиального типа.
 */
template<class T>
T GetRandomValue() {
    // Определение приближённого максимального хранимого тривиальным типом значения.
    return rand() % ((1 << ((sizeof(T) * 8) - 1)) - 1);
}


/**
 * \brief Специализация метода возвращающего произвольный элемент для double.
 */
template<>
double GetRandomValue<double>() {
    return static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
}


/**
 * \brief Специализация метода возвращающего элемент для сложного объекта.
 */
template<>
TestSortElement GetRandomValue<TestSortElement>() {
    return TestSortElement();
}


/**
 * \brief Функция произвольно заполняющая тестовый массив.
 */
template<class T>
std::vector<T> RandomInitialCondition(const size_t len) {
    std::vector<T> buf(len);
    for (size_t i = 0; i < len; ++i) {
        buf[i] = GetRandomValue<T>();
    }
    return buf;
}


/**
 * \brief Функция частичного перемешивающая массива данных.
 */
template<class T>
void NearlyMix(std::vector<T>& buf) {
    size_t max = static_cast<size_t>(std::floor(static_cast<double>(buf.size()) * 0.2 + 0.5));
    for (size_t i = 0; i < max; ++i) {
        size_t l = rand() % (buf.size() - 2);
        size_t k = rand() % (buf.size() - 2);
        if (l == k) {
            k = l + 1;
        }
        T value = buf[l];
        buf[l] = buf[k];
        buf[k] = value;
    }
}


/**
 * \brief Функция возвращающая элемент по возрастанию для тривиального типа.
 */
template<class T>
T GetUpValue(size_t i) {
    return i;
}


/**
 * \brief Специализация функции возвращающей элемент по возрастанию для double.
 */
template<>
double GetUpValue<double>(size_t i) {
    return static_cast<double>(i) / static_cast<double>(RAND_MAX);
}


/**
 * \brief Функция заполняющая тестовый массив частично отсортированными данными.
 */
template<class T>
std::vector<T> NearlySortedInitialCondition(const size_t len) {
    std::vector<T> buf(len);
    for (size_t i = 0; i < len; ++i) {
        buf[i] = GetUpValue<T>(i);
    }
    NearlyMix(buf);
    return buf;
}


/**
 * \brief Специализация функции заполняющей частично отсортированно тестовый массив для пользовательского типа.
 */
template<>
std::vector<TestSortElement> NearlySortedInitialCondition<TestSortElement>(const size_t len) {
    std::vector<TestSortElement> buf(len);
    for (size_t i = 0; i < len; ++i) {
        buf[i] = TestSortElement();
    }
    std::sort(buf.begin(), buf.end());
    NearlyMix(buf);
    return buf;
}


/**
 * \brief Функция возвращающая элемент для тривиального типа по убыванию.
 */
template<class T>
T GetDownValue(size_t i, size_t len) {
    return len - i;
}


/**
 * \brief Специализация функции возвращающей элемент для double по убыванию.
 */
template<>
double GetDownValue<double>(size_t i, size_t len) {
    return static_cast<double>(len - i) / static_cast<double>(RAND_MAX);
}


/**
 * \brief Функция заполняющая тестовый массив по убыванию.
 */
template<class T>
std::vector<T> ReverseSortedInitialCondition(const size_t len) {
    std::vector<T> buf;
    for (size_t i = 0; i < len; ++i) {
        buf[i] = GetDownValue<T>(i, len);
    }
    return buf;
}


/**
 * \brief Специализация функции заполняющей тестовый массив по убыванию для TestSortElement.
 */
template<>
std::vector<TestSortElement> ReverseSortedInitialCondition<TestSortElement>(const size_t len) {
    std::vector<TestSortElement> buf(len);
    for (size_t i = 0; i < len; ++i) {
        buf[i] = TestSortElement();
    }
    auto minore = [](const TestSortElement &a, const TestSortElement &b) {
        return a > b;
    };
    std::sort(buf.begin(), buf.end(), minore);
    return buf;
}


/**
 * \brief Функция заполняющая тестовый массив повторяющимися значениями.
 */
template<class T>
std::vector<T> FewUniqueInitialCondition(const size_t len) {
    std::vector<T> buf;
    // Получение количества частей массива соотвествующее степени длинны массива
    size_t k = static_cast<size_t>(std::log(static_cast<double>(len)));
    // Получение количества повторяющихся элементов
    size_t m = static_cast<size_t>(std::floor(static_cast<double>(len) / static_cast<double>(k) + 0.5));

    for (size_t i = 0; i < m; ++i) {
        T value = GetRandomValue<T>();
        for (size_t j = 0; j < k; ++j) {
            buf.push_back(value);
        }
    }
    return buf;
}


/**
 * \brief Класс реализующий заполнение различных массивов для тестирования алгоритмов сортировки.
 */
class TestSortingArrayFactory {
    std::array<std::vector<char>, ARRAYS_NUM>            _char_array;
    std::array<std::vector<int>, ARRAYS_NUM>             _int_array;
    std::array<std::vector<double>, ARRAYS_NUM>          _double_array;
    std::array<std::vector<TestSortElement>, ARRAYS_NUM> _elements_array;

public:
    enum class InitialCondition {
        RANDOM,
        NEARLY_SORTED,
        REVERSED,
        FEW_UNIQUE
    };

    TestSortingArrayFactory(InitialCondition init_condition) {
        size_t i = 0;
        for (size_t len = MIN_ARRAY_LEN; len < MAX_ARRAY_LEN; len <<= 1, ++i) {
            switch(init_condition) {
            case InitialCondition::RANDOM:
                _char_array[i]     = RandomInitialCondition<char>(len);
                _int_array[i]      = RandomInitialCondition<int>(len);
                _double_array[i]   = RandomInitialCondition<double>(len);
                _elements_array[i] = RandomInitialCondition<TestSortElement>(len);
                break;
            case InitialCondition::NEARLY_SORTED:
                _char_array[i]     = NearlySortedInitialCondition<char>(len);
                _int_array[i]      = NearlySortedInitialCondition<int>(len);
                _double_array[i]   = NearlySortedInitialCondition<double>(len);
                _elements_array[i] = NearlySortedInitialCondition<TestSortElement>(len);
                break;
            case InitialCondition::REVERSED:
                _char_array[i]     = ReverseSortedInitialCondition<char>(len);
                _int_array[i]      = ReverseSortedInitialCondition<int>(len);
                _double_array[i]   = ReverseSortedInitialCondition<double>(len);
                _elements_array[i] = ReverseSortedInitialCondition<TestSortElement>(len);
                break;
            case InitialCondition::FEW_UNIQUE:
                _char_array[i]     = FewUniqueInitialCondition<char>(len);
                _int_array[i]      = FewUniqueInitialCondition<int>(len);
                _double_array[i]   = FewUniqueInitialCondition<double>(len);
                _elements_array[i] = FewUniqueInitialCondition<TestSortElement>(len);
                break;
            }
        }
    }

    const std::array<std::vector<char>, ARRAYS_NUM>& getCharArray() { return _char_array; }
    const std::array<std::vector<int>, ARRAYS_NUM>& getIntArray() { return _int_array; }
    const std::array<std::vector<double>, ARRAYS_NUM>& getDoubleArray() { return _double_array; }
    const std::array<std::vector<TestSortElement>, ARRAYS_NUM>& getElementsArray() { return _elements_array; }
};
} // details

class BubbleSortTest {
    typedef details::TestSortingArrayFactory TestSortingArrayFactory;
    typedef TestSortingArrayFactory::InitialCondition InitialCondition;
    std::shared_ptr<sort::exchange::BubbleSort> _sort;

public:
    BubbleSortTest() {
        TestSortingArrayFactory factory(InitialCondition::FEW_UNIQUE);
        for (const auto &value : factory.getElementsArray()[3]) {
            std::cout << "[" << value << "]\n";
        }
    }
};
} // test


BOOST_AUTO_TEST_CASE(TestCppExamples) {
    LOG_TO_STDOUT;
    // Инициализация рандом-генератора.
    std::srand(std::time(NULL));


    test::BubbleSortTest bubble_sort;

}
