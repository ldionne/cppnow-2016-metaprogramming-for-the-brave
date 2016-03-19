// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#include <tuple>

#include "my_tuple_cat.hpp"


int main() {
    std::tuple<int, char, float> ts;
    ::tuple_cat(ts, ts);
}
