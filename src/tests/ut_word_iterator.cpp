#ifndef BOOST_STATIC_LINK
#   define BOOST_TEST_DYN_LINK
#endif // BOOST_STATIC_LINK

#define BOOST_TEST_MODULE CppExamples
#define BOOST_AUTO_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>

#include <string>
#include <algorithm>
#include <initializer_list>


#include "Log.hpp"


namespace test {

/**
 * \brief Класс реализующий простейщую итерацию по словам.
 */
class WordIterator {
    std::string _str;
    std::string::iterator _begin_current_word;
    std::string::iterator _end_current_word;

    /**
     * \brief Метод получения списка разделителей слов.
     */
    std::initializer_list<char> getDelimitersList() {
        static auto list = {' ', '\n', '\r', '\t', ',', '.', '?', '!', ':', ';', '[', '{', '(', ')', '}', ']'};
        return list;
    }

    /**
     * \brief Метод получения конца слова по разделителю относительно текущего начала.
     */
    std::string::iterator getEndWordIterator() {
        auto list = getDelimitersList();
        return std::find_first_of(_begin_current_word, _str.end(), list.begin(), list.end());
    }

    /**
     * \brief Метод получения начала слова по разделителю относительно текущего конца.
     */
    std::string::iterator getNextBeginWordIterator() {
        auto list = getDelimitersList();
        for(auto iter = _end_current_word; iter not_eq _str.end(); ++iter) {
            if (std::find(list.begin(), list.end(), *iter) == list.end()) {
                return iter;
            }
        }
        return _str.end();
    }

public:
    /**
     * \brief Конструктор end итератора.
     */
    WordIterator()
        : _begin_current_word(_str.end())
        , _end_current_word(_str.end()) {
        LOG(DEBUG) << "Инициализация END итератора.";
    }

    /**
     * \brief Конструктор begin итератора.
     */
    WordIterator(const std::string &str)
        : _str(str) {
        _end_current_word = _str.begin();
        _begin_current_word = getNextBeginWordIterator();
        _end_current_word = getEndWordIterator();
        LOG(DEBUG) << "Инициализация BEGIN итератора.";
    }

     /**
     * \brief Оператор разименования текущего слова.
     */
    std::string operator * () {
        std::string str(_begin_current_word, _end_current_word);
        LOG(DEBUG) << "Запрошено слово: \"" << str << "\"";
        return str;
    }

    /**
     * \brief Пред инкреметнный оператор.
     */
    void operator ++ () {
        LOG(DEBUG) << "Получить следующее слово.";
        // Для End итератора не нужно выполнять итерацию
        bool is_cur_end = (_str.end() == _begin_current_word and _begin_current_word == _end_current_word);
        if (not is_cur_end) {
            _begin_current_word = getNextBeginWordIterator();
            _end_current_word = getEndWordIterator();
        }
    }

    /**
     * \brief Пост инкреметнный оператор.
     */
    WordIterator operator ++ (int) {
        WordIterator word_iter(*this);
        ++(*this);
        return word_iter;
    }

    bool operator not_eq (const WordIterator &iter) {
        // Определить, что входящий итератор End
        bool is_ext_end = (iter._str.end() == iter._begin_current_word and iter._begin_current_word == iter._end_current_word);

        // Определить, что текущий итератор End
        bool is_cur_end = (_str.end() == _begin_current_word and _begin_current_word == _end_current_word);

        // End итераторы считаются равными
        if (is_ext_end and is_cur_end) {
            return false;
        }

        // При сравнение с самим собой считаем итераторы идентичными и завершаем сравнения
        return (this not_eq &iter);
    }
};
} // test


BOOST_AUTO_TEST_CASE(TestWordIterator) {
    LOG_TO_STDOUT;

    // Для избежания зацикливания при тестировании, цилк лучше не применять.

    // Тестирование смешанного случая
    test::WordIterator iter_1(" test string   with ,.?!:;[{()]symbols "), end;
    BOOST_CHECK(*iter_1++ == "test"    and (iter_1 not_eq end));
    BOOST_CHECK(*iter_1++ == "string"  and (iter_1 not_eq end));
    BOOST_CHECK(*iter_1++ == "with"    and (iter_1 not_eq end));
    BOOST_CHECK(*iter_1++ == "symbols" and not (iter_1 not_eq end)); // на данном этапе итератор должен стать END

    // Тестирование текста из разделителей слов
    test::WordIterator iter_2(" ,.?!:;[{()]    ,.?!:;[{()]");
    BOOST_CHECK(*iter_2++ == "" and not (iter_2 not_eq end));
    BOOST_CHECK(*iter_2++ == "" and not (iter_2 not_eq end));

    // Тестирование текста из одного слова
    test::WordIterator iter_3("one_word");
    BOOST_CHECK(*iter_3++ == "one_word" and not (iter_3 not_eq end));
    BOOST_CHECK(*iter_3++ == ""         and not (iter_3 not_eq end));
}
