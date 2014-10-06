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
#include <multimap>
#include <multiset>
#include <unordered_map>
#include <unordered_set>
#include <unordered_multimap>
#include <unordered_multiset>
#include <stack>
#include <queue>
#include <priority_queue>

#include "Log.hpp"

class Container {
};


class SequancedContainer
	: public Container
{};


class AssociativeContainer 
	: public Container
{};


class UnorderedAssociativeContainer
	: public Container
{};


class AdaptorContainer
	: public Container
{};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Array
	: public SequancedContainer
{};


class Vector
	: public SequancedContainer
{};


class Deque
	: public SequancedContainer
{};


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
}


BOOST_AUTO_TEST_CASE(TestStlPtrs) {
    LOG_TO_STDOUT;
}


BOOST_AUTO_TEST_CASE(TestStlAlgorithms) {
    LOG_TO_STDOUT;
}
