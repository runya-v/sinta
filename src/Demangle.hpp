#pragma once

#include <string>


class Demangle {
    std::string _demangle;

public:
    Demangle(const std::string &name);

    operator std::string ();
};
