#include <cstdlib>
#include <ctime>
#include <iostream>

#include "NumberGenerator.hpp"

static const int MIN_COUNT = 2;
static const int MAX_COUNT = 1000000;
static const int MAX_VALUE = 10000;


NumberGenerator::NumberGenerator(int count) {
    int c = (MIN_COUNT <= count and MAX_COUNT >= count) ? count : (MAX_COUNT * 0.5);
    for(int i = 0; i < c; ++i) {
        std::srand(std::time(0));
        std::cout << std::rand() % MAX_VALUE << "\n" << std::flush;
    }
}


NumberGenerator::~NumberGenerator() {

}
