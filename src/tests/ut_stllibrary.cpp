#ifndef BOOST_STATIC_LINK
#   define BOOST_TEST_DYN_LINK
#endif // BOOST_STATIC_LINK

#define BOOST_TEST_MODULE Cpp11
#define BOOST_AUTO_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>

#include <sstream>
#include <array>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <set>
#include <stack>
#include <queue>

#include "Log.hpp"

class Container {
public:
    Container() {
        LOG(TEST);
    }
};


class SequancedContainer
    : public Container
{
public:
    SequancedContainer() {
        LOG(TEST);
    }
};


class AssociativeContainer
    : public Container
{
public:
    AssociativeContainer() {
        LOG(TEST);
    }
};


class UnorderedAssociativeContainer
    : public Container
{
public:
    UnorderedAssociativeContainer() {
        LOG(TEST);
    }
};


class AdaptorContainer
    : public Container
{
public:
    AdaptorContainer() {
        LOG(TEST);
    }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Array
    : public SequancedContainer
{
public:
    Array() {
        LOG(TEST) << "Access Complexitive: O(1)";
        LOG(TEST) << "Constructor use aggregate initialization.";

        std::array<int, 3> a1{ {2, 3, 1} };
        std::stringstream ss;
        for(auto &s : a1) {
            ss << s << ',';
        }
        LOG(TEST) << "std::array<int, 3> a1: " << ss.str();

        std::array<std::string, 3> a3 = { {std::string("a"), "b", "c"} };
        ss.str("");
        for(auto &s : a3) {
            ss << s << ',';
        }
        LOG(TEST) << "std::array<std::string, 3> a3: " << ss.str();

        LOG(TEST) << "Support generalised algorithms";
        std::sort(a1.begin(), a1.end());
        ss.str("");
        for(auto &s : a1) {
            ss << s << ',';
        }
        LOG(TEST) << "std::array<int, 3> a1 (sort): " << ss.str();

        std::array<int, 3> a2 = {1, 2, 3};
        ss.str("");
        std::reverse_copy(a2.begin(), a2.end(), std::ostream_iterator<int>(ss, ","));
        LOG(TEST) << "std::array<int, 3> a2 (reverse_copy): " << ss.str();
    }
};


class Vector
    : public SequancedContainer
{
public:
    Vector() {
        LOG(TEST) << "Free access by index Complexitive: O(1)";
        LOG(TEST) << "Insert/Delete to end Complexitive: O(1)";
        LOG(TEST) << "Insert/Delete Complexitive: O(n)";
        LOG(TEST) << "Find Complexitive: O(n)";
        LOG(TEST) << "Find sorted Complexitive: O(ln(n))";
    }
};


class Deque
    : public SequancedContainer
{
public:
    Deque() {
        LOG(TEST) << "Free access by index Complexitive: O(1)";
        LOG(TEST) << "Insert/Delete to end & to begin Complexitive: O(1)";
        LOG(TEST) << "Insert/Delete Complexitive: O(n)";
        LOG(TEST) << "Insert/Delete doesn`t crashed saved iterators";
        LOG(TEST) << "Insert/Delete doesn`t crashed saved iterators";

    }
};


class ForwardList
    : public SequancedContainer
{};


class List
    : public SequancedContainer
{};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Map
    : public AssociativeContainer
{};


class Set
    : public AssociativeContainer
{};


class MultiMap
    : public AssociativeContainer
{};


class MultiSet
    : public AssociativeContainer
{};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class UnorderedMap
    : public UnorderedAssociativeContainer
{};


class UnorderedSet
    : public UnorderedAssociativeContainer
{};


class UnorderedMultimap
    : public UnorderedAssociativeContainer
{};


class UnorderedMultiset
    : public UnorderedAssociativeContainer
{};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Stack
    : public AdaptorContainer
{};


class Queue
    : public AdaptorContainer
{};


class PriorityQueue
    : public AdaptorContainer
{};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


BOOST_AUTO_TEST_CASE(TestStlContainers) {
    LOG_TO_STDOUT;
    Array();
}


BOOST_AUTO_TEST_CASE(TestStlPtrs) {
    LOG_TO_STDOUT;
}


BOOST_AUTO_TEST_CASE(TestStlAlgorithms) {
    LOG_TO_STDOUT;
}
