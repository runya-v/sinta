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

#include "Bench.hpp"
#include "Chart.hpp"
#include "Demangle.hpp"
#include "Log.hpp"
#include "ForEachTuple.hpp"


//class TimeSegment {
//private:
//    TimeSegment();
//
//    operator uint32_t () {
//        return 0;
//    }
//};
//
//
//template<std::size_t ... BlockSizes>
//struct ArraySizes {
//    typedef std::tuple<BlockSizes...> Tuple;
//
//    enum {
//        NUM_BLOCKS = sizeof...(BlockSizes)
//    };
//    Tuple _sizes;
//};
//
//
//template<class DataType>
//class FromBegin {
//public:
//    template<class ContainerType>
//    void operator(uint32_t &result) {
//        ContainerType container;
//
//        for () {
//            TimeSegment segment;
//            container.insert();
//        }
//    }
//
//    template<class ContainerType, class...Results>
//    FromBegin(ContainerType container, std::tuple<Results...>) {
//        ContainerType
//    }
//};
//
////template<>
////class FromEnd {};
////
////template<>
////class FromRandom {};
//
//
//
//
//
//
//template<class AraySizesType>
//struct Policy {
//    std::shared_ptr<TimeSegment> _time_segment;
//    AraySizesType::Tuple _time_results;
//};
//
//
//template<class DataType, class AraySizesType, template<class, class> class MethodType>
//class Fill : Policy<AraySizesType>
//{
//public:
//    typedef<class ContainerType>
//    void operator() (ContainerType &container) {
//        ForEachTuple(AraySizesType()._sizes, MethodType<DataType, AraySizesType>(container, _time_segment, _time_results));
//    }
//};
//
//
//template<class DataType, class MethodType>
//class Insert : public Policy {};
//
//template<>
//class Concatenate : public Policy {};
//
//template<>
//class Find : public Policy {};
//
//template<>
//class Sort : public Policy {};
//
//template<>
//class Erase : public Policy {};
//
//template<>
//class Cut : public Policy {};
//
//template<>
//class Delete : public Policy {};
//
//
//template<class PolicyType, class ... ContainerTypes>
//class Containers {
//public:
//    SequancedContainers() {
//        ForEachTuple(std::make_tuple({ContainerTypes...}), PolicyType);
//    }
//};
//
//
//template<class PolicyType>
//class Sequanced
//    : public Containers<PolicyType, std::vector, std::deque, std::list, std::forvard_list>
//{};
//
//
//template<class PolicyType>
//class Resized
//    : public Containers<PolicyType, std::array, std::vector, std::deque, std::list, std::forvard_list>
//{};
//
//
//template<class PolicyType>
//class Associatived
//    : public Containers<PolicyType, std::set, std::map>
//{};
//
//
//template<class PolicyType>
//class UnorderedAssociatived
//    : public Containers<PolicyType, std::unordered_set, std::unordered_map>
//{};
//
//
//template<class PolicyType>
//class Adaptored
//    : public Containers<PolicyType, std::stack, std::queue, std::priority_queue>
//{};
//
//
//template<class ContainerTypes>
//class Bench {
//    std::shared_ptr<Chart> _chart;
//
//public:
//    Bench() {
//        _chart = std::make_shared<Chart>(Demangle(Bench));
//
//        PolicyType
//
//        for (container : {ContainerTypes::...}) {
//            _chart->newDiagram(Demangle(PolicyType), title, unit);
//            _chart->newResult(serie, group, value);
//        }
//        _chart->output();
//
//    }
//};
//
//
//
//
//class MakeBench {
//public:
//    MakeBench() {
//        Bench<Sequanced<Fill<TypedSimpleData, FromBegin>>>();
//        //Bench<AssociativeContainers<Fill<TypedSimpleData, FromBegin>>>();
//        //Bench<UnorderedAssociativeContainers<Fill<TypedSimpleData, FromBegin>>>();
//        //Bench<AdaptorContainers<Fill<TypedSimpleData, FromBegin>>>();
//        //
//        //Bench<SequancedContainers<Fill<TypedSimpleData, FromBegin>>>();
//        //Bench<AssociativeContainers<Fill<TypedSimpleData, FromBegin>>>();
//        //Bench<UnorderedAssociativeContainers<Fill<TypedSimpleData, FromBegin>>>();
//        //Bench<AdaptorContainers<Fill<TypedSimpleData, FromBegin>>>();
//    }
//};
//
//
//// benchmarking procedure
//template<
//    class Container,
//    class DurationUnit,
//    template<class> class CreatePolicy,
//    template<class> class ...TestPolicy>
//void bench(const std::string& type, const std::initializer_list<int> &sizes) {
//    for (auto size : sizes) {
//        Clock::duration duration;
//
//        for (std::size_t i = 0; i < REPEAT_EACH_TEST; ++i) {
//            auto container = CreatePolicy<Container>::make(size);
//            Clock::time_point tp_start = Clock::now();
//            run<TestPolicy...>(container, size);
//            Clock::time_point tp_stop = Clock::now();
//            duration += tp_stop - tp_start;
//        }
//        _chart->newResult(type, std::to_string(size), ch::duration_cast<DurationUnit>(duration).count() / REPEAT_EACH_TEST);
//    }
//    CreatePolicy<Container>::clean();
//}
//
//
//class Container {
//public:
//    Container() {
//        LOG(TEST);
//    }
//};
//
//
//class SequancedContainer
//    : public Container
//{
//public:
//    SequancedContainer() {
//        LOG(TEST);
//    }
//};
//
//
//class AssociativeContainer
//    : public Container
//{
//public:
//    AssociativeContainer() {
//        LOG(TEST);
//    }
//};
//
//
//class UnorderedAssociativeContainer
//    : public AssociativeContainer
//{
//public:
//    UnorderedAssociativeContainer() {
//        LOG(TEST);
//    }
//};
//
//
//template<class C>
//class AdaptorContainer
//    : public Container
//{
//    C _container;
//
//public:
//    AdaptorContainer() {
//        LOG(TEST);
//    }
//};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//class Array
//    : public SequancedContainer
//{
//public:
//    Array() {
//        LOG(TEST) << "Access Complexitive: O(1)";
//        LOG(TEST) << "Constructor use aggregate initialization.";
//
//        std::array<int, 3> a1{ {2, 3, 1} };
//        std::stringstream ss;
//        for(auto &s : a1) {
//            ss << s << ',';
//        }
//        LOG(TEST) << "std::array<int, 3> a1: " << ss.str();
//
//        std::array<std::string, 3> a3 = { {std::string("a"), "b", "c"} };
//        ss.str("");
//        for(auto &s : a3) {
//            ss << s << ',';
//        }
//        LOG(TEST) << "std::array<std::string, 3> a3: " << ss.str();
//
//        LOG(TEST) << "Support generalised algorithms";
//        std::sort(a1.begin(), a1.end());
//        ss.str("");
//        for(auto &s : a1) {
//            ss << s << ',';
//        }
//        LOG(TEST) << "std::array<int, 3> a1 (sort): " << ss.str();
//
//        std::array<int, 3> a2 = {1, 2, 3};
//        ss.str("");
//        std::reverse_copy(a2.begin(), a2.end(), std::ostream_iterator<int>(ss, ","));
//        LOG(TEST) << "std::array<int, 3> a2 (reverse_copy): " << ss.str();
//    }
//};
//
//
//class Vector
//    : public SequancedContainer
//{
//public:
//    Vector() {
//        LOG(TEST) << "Free access by index Complexitive: O(1)";
//        LOG(TEST) << "Insert/Delete to end Complexitive: O(1)";
//        LOG(TEST) << "Insert/Delete Complexitive: O(n)";
//        LOG(TEST) << "Find Complexitive: O(n)";
//        LOG(TEST) << "Find sorted Complexitive: O(ln(n))";
//    }
//};
//
//
//class Deque
//    : public SequancedContainer
//{
//public:
//    Deque() {
//        LOG(TEST) << "Free access by index Complexitive: O(1)";
//        LOG(TEST) << "Insert/Delete to end & to begin Complexitive: O(1)";
//        LOG(TEST) << "Insert/Delete Complexitive: O(n)";
//        LOG(TEST) << "Insert/Delete doesn`t crashed saved iterators";
//        LOG(TEST) << "Insert/Delete doesn`t crashed saved iterators";
//
//    }
//};
//
//
//class ForwardList
//    : public SequancedContainer
//{};
//
//
//class List
//    : public SequancedContainer
//{};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//class Map
//    : public AssociativeContainer
//{};
//
//
//class Set
//    : public AssociativeContainer
//{};
//
//
//class MultiMap
//    : public AssociativeContainer
//{};
//
//
//class MultiSet
//    : public AssociativeContainer
//{};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//class UnorderedMap
//    : public UnorderedAssociativeContainer
//{};
//
//
//class UnorderedSet
//    : public UnorderedAssociativeContainer
//{};
//
//
//class UnorderedMultimap
//    : public UnorderedAssociativeContainer
//{};
//
//
//class UnorderedMultiset
//    : public UnorderedAssociativeContainer
//{};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//class Stack
//    : public AdaptorContainer
//{};
//
//
//class Queue
//    : public AdaptorContainer
//{};
//
//
//class PriorityQueue
//    : public AdaptorContainer
//{};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
////class Example_1 {
////public:
////    Example_1() {
////        LOG(TEST);
////        std::map<int, std::string> m;
////        m.insert(std::make_pair(13, "test str"));
////        auto it = m.find(13);
////        if (it != m.end()) {
////            LOG(TEST) << "[" << it->first << ";" << it->second << "]";
////        }
////    }
////};
//
//
//class BenchTest {
//public:
//    BenchTest() {
//        //Launch all the graphs
//        Bench<
//            TrivialSmall,
//            TrivialMedium,
//            TrivialLarge,
//            TrivialHuge,
//            TrivialMonster,
//            NonTrivialStringMovable,
//            NonTrivialStringMovableNoExcept,
//            NonTrivialArray<32>>
//        ("charts.html");
//
//        //Generate the graphs
//        graphs::output(graphs::Output::GOOGLE);
//    }
//};


BOOST_AUTO_TEST_CASE(TestBench) {
    LOG_TO_STDOUT;
    Bench<
        TrivialSmall,
        TrivialMedium,
        TrivialLarge,
        TrivialHuge,
        TrivialMonster,
        NonTrivialStringMovable,
        NonTrivialStringMovableNoExcept,
        NonTrivialArrayMedium>
        ("associated");
}
