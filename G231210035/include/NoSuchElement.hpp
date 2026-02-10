#ifndef NOSUCHELEMENT_HPP
#define NOSUCHELEMENT_HPP

#include <iostream>
using namespace std;

#include "Exception.hpp"

class NoSuchElement : public Exception {
public:
    NoSuchElement(const string &msg);
};

#endif
