#include <cstdlib>
#include <ctime>

#include "NumberGenerator.hpp"

static const int MIN_COUNT = 2;
static const int MAX_COUNT = 1000000;
static const int MAX_VALUE = 10000;


NumberGenerator::NumberGenerator(int count) {
    int c = (MIN_COUNT <= count and MAX_COUNT >= count) ? count : (MAX_COUNT * 0.5);
    for(int i = 0; i < count; ++i) {
        std::srand(std::time(0));
        int random_variable = std::rand() % MAX_VALUE;
    }
}
