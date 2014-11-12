#ifndef BOOST_STATIC_LINK
#   define BOOST_TEST_DYN_LINK
#endif // BOOST_STATIC_LINK

#define BOOST_TEST_MODULE CppExamples
#define BOOST_AUTO_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>

#include <vector>
#include <cstdlib>
#include <ctime>

#include "Log.hpp"


class Example_1 {
public:
    Example_1() {
        LOG(TEST);
        std::map<int, std::string> m;
        m.insert(std::make_pair(13, "test str"));
        auto it = m.find(13);
        if (it != m.end()) {
            LOG(TEST) << "[" << it->first << ";" << it->second << "]";
        }
    }
};


class Example_2 {
public:
    enum Directions {
        UP = 1, DOWN = 2, LEFT = 4, RIGHT = 8
    };

    enum Samples {
        S0, S1, S2, S3, S4, S5
    };

    class Robot {
    public:
        long x;
        long y;
        long _s;

        Robot(long s)
            : x(0), y(0), _s(s)
        {
            LOG(TEST);
        }

        int checkMove(int d) {
            LOG(TEST);
            int res = 1;
            return res;
        }

        int isMove(int d, int s) {
            LOG(TEST);
            switch (_s) {
                case 0: return 0;
                case 1: return d ^ s;
                case 2: return d | s;
                case 3: return d & s; // Очевидно!
                case 4: return d << s;
                case 5: return d && s;
            }
        }

        int move(int d, long dist = 1) {
            if (not checkMove(d)) return 0;
            if (isMove(d, UP))    { LOG(TEST) << "y -= dist"; y -= dist; }
            if (isMove(d, DOWN))  { LOG(TEST) << "y += dist"; y += dist; }
            if (isMove(d, LEFT))  { LOG(TEST) << "x -= dist"; x -= dist; }
            if (isMove(d, RIGHT)) { LOG(TEST) << "x += dist"; x += dist; }
            return 1;
        }
    };


    Example_2() {
        LOG(TEST);
        Robot r0(S0);
        r0.move(LEFT | UP);
        Robot r1(S1);
        r1.move(LEFT | UP);
        Robot r2(S2);
        r2.move(LEFT | UP);
        Robot r3(S3);
        r3.move(LEFT | UP);
        Robot r4(S4);
        r4.move(LEFT | UP);
        Robot r5(S5);
        r5.move(LEFT | UP);
    }
};


class Example_3 {
public:
    class Student {
    public:
        int age;
    };

    std::vector<Student*> studs;
    const std::vector<Student*> &r = studs;

    Example_3() {
        LOG(TEST) << "start";
        Student s1;
        Student s2;
        Student s3;
        studs.push_back(&s1);
        studs.push_back(&s2);
        studs.push_back(&s3);
        std::vector<Student*>::const_reverse_iterator i;
        //for (i = r.rend(); i != r.rbegin(); ++i) {
        for (i = r.rbegin(); i != r.rend(); ++i) {
            LOG(TEST);
            (*i)->age = 20;
        }
    }
};


class Example_4 {
public:
    char c[6] = {1, 2, 3, 4, 5};
    int p[6] = {1, 2, 3, 4, 5};

    Example_4() {
        LOG(TEST) << "start";
        LOG(TEST) << (int)*(c + 3);
        LOG(TEST) << *(p + 3);
    }
};


class Example_5 {
public:
    class A {
    public:
        void f() {LOG(TEST) << 1;}
        void f(int) {LOG(TEST) << 2;}
    };

    class B : public A {
    public:
        using A::f;
        void f(bool) {LOG(TEST) << 3;}
    };


    Example_5() {
        LOG(TEST) << "start";
        B b;
        b.f(true);
        b.f(2);
        b.f();
    }
};


namespace X {
    int x = 5;

    namespace Y {
        int x = 2;

        void f() {
            for (int i = 1; i < 10; ++i) {
                int x = 10;
                X::x += Y::x * x;
            }
            LOG(TEST) << X::x;
        }
    }
}

class Example_6 {
public:
    Example_6() {
        X::Y::f();
    }
};


class Example_7 {
    class A {
    public:
        A() {
            LOG(TEST);
        }
    };

    class B : virtual public A {
    public:
        B() {
            LOG(TEST);
        }
    };

    class C : public B {
    public:
        C() {
            LOG(TEST);
        }
    };

public:
    Example_7() {
        C();
    }
};


class Example_8 {
public:
    Example_8() {
        int x, y;
        int i = x = y = 1;
        //int *p = &x++; // временная переменная!
        int *q = &++x;
        int r = y++;
        int t = ++i;
        int p[4] = {0};
        LOG(TEST) << *p << "," << *q << "," << r << "," << t;
        //p[i] = i++; // действие не определено
        //LOG(TEST) << p[0] << "," << p[1] << "," << p[2] << "," << p[3];
    }
};

class Example_9 {
    void f(int a, int b, int c) {
        LOG(TEST) << a << "," << b << "," << c;
    }

public:
    Example_9() {
        int a = 100;
        int b = 200;
        int &c = a;
        f(a, b, c);
        c = b;
        a = 300 - a;
        LOG(TEST) << a << "," << b << "," << c;
    }
};


class Example_10 {
    class A {
    public:
        A(int)
        {
            LOG(TEST);
        }
    };

    class B {
    public:
        B(A)
        {
            LOG(TEST);
        }
    };

    class C {
    public:
        C()
        {
            LOG(TEST);
        }

        C(A)
        {
            LOG(TEST);
        }

        operator B()
        {
            LOG(TEST);
            return B(A(10));
        }
    };

    void f(A)
    {
        LOG(TEST);
    }

    void g(B)
    {
        LOG(TEST);
    }

    void h(C)
    {
        LOG(TEST);
    }

public:
    Example_10() {
        f(10); // Xc(int)
        g(C()); // C() -> operator B()
        g(C(10)); // C(int -> A(int)) -> operator B()
        h(A(10)); // A(int) -> C(Xc)
        // g(10); error // int
        // h(10); error // int
    }
};


class Example_11 {
    class A {
    public:
        A() {
        }

        A(const A&) {
            LOG(DEBUG) << "test " << std::hex << this;
        }

        ~A() {
            LOG(DEBUG) << std::hex << this;
        }
    };
public:
    Example_11() {
        try{
            LOG(DEBUG) << "A a1";
            A a1;
            LOG(DEBUG) << "A a2 = a1";
            A a2 = a1;
            LOG(DEBUG) << "A a3(a2)";
            A a3(a2);
            LOG(DEBUG) << "throw a3";
            throw a3;
        }
        catch (A a) {
            LOG(DEBUG) << "catch (A a)";
        }
    }
};


class Example_12 {
    struct List {
        List *_next;
        List *_direction;
        int _id;

        List()
            : _next(nullptr)
            , _direction(nullptr)
            , _id(-1)
        {}
    };

    class ListConstMemberLineTimeCloner {
        List *_out;

    public:
        ListConstMemberLineTimeCloner(List *in) {
            if (in) {
				// Create combo list
				List *head = in;
                _out = new List;
				while (in->_next) {
					_out->_id = in->_id;
					_out->_direction = in->_next;
					in->_next = _out;
					in = _out->_direction;
					_out->_next = new List;
					_out = _out->_next;
				}
				_out->_id = in->_id;
				in->_next = _out;

				in = head;
				_out = in->_next;
				while (_out) {
					_out->_direction = _out->_direction->_next;
					in->_next = _out->_direction;
					_out->_next = in->_next;
					_out = in->_next->_next;
				}

				in = head;
				_out = in->_next;
				head = _out;
				while (in) {
					in->_next = _out->_next;
					_out->_next = in->_next->_next;
					_out = _out->_next;
					in = in->_next;
				}
				_out = head;
            }
        }

        operator List* () {
            return _out;
        }
    };

    static constexpr uint32_t LIST_SIZE = 3;

public:
    Example_12() {
        // Generate Input List;
        List* list_arr[LIST_SIZE];

        for (uint32_t i = 0; i < LIST_SIZE; ++i) {
            list_arr[i] = new List;
            list_arr[i]->_id = i;
        }

        std::srand(std::time(0));
        for (uint32_t i = 0; i < LIST_SIZE; ++i) {
			uint32_t last = LIST_SIZE - 1;
            list_arr[i]->_next = (i < last) ? list_arr[i + 1] : nullptr;
            list_arr[i]->_direction = list_arr[std::rand() % last];
            LOG(DEBUG) << "generate: [" << list_arr[i]->_id << "]->[" << list_arr[i]->_direction->_id << "]; ";
        }

        // Clone
        List *in_list = list_arr[0];
        List *cloned_list = ListConstMemberLineTimeCloner(in_list);

        for (uint32_t i = 0; i < LIST_SIZE; ++i) {
            LOG(DEBUG)
                << "in: [" << in_list->_id << "]->[" << in_list->_direction->_id << "]; "
                << "out: [" << cloned_list->_id << "]->[" << cloned_list->_direction->_id << "]";
            in_list = in_list->_next;
            cloned_list = cloned_list->_next;
        }
    }
};


class Example_13 {
public:
    Example_13() {
    }
};

BOOST_AUTO_TEST_CASE(TestCppExamples) {
    LOG_TO_STDOUT;

    //Example_1();
    //Example_2();
    //Example_3();
    //Example_4();
    //Example_5();
    //Example_6();
    //Example_7();
    //Example_8();
    //Example_9();
    //Example_10();
    //Example_11();
    Example_12();
}
