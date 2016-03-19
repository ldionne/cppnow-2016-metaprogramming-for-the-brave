// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#include <boost/hana/tuple.hpp>
#include "my_tuple_cat.hpp"
namespace hana = boost::hana;


int main() {
    hana::tuple<int, char, float> ts;
    ::tuple_cat(ts, ts);
}
