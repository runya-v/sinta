#pragma once


#include <thread>
#include <memory>

class NumberGenerator {
    typedef std::shared_ptr<std::thread> ThreadPtr;

    ThreadPtr _thread;

public:
    explicit NumberGenerator(int count);
    virtual ~NumberGenerator();
};
