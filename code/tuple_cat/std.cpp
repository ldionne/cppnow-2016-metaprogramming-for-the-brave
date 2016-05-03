// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#include <boost/hana/tuple.hpp>

#include <cassert>
#include <string>

#include "std.hpp"
namespace hana = boost::hana;


int main() {
    hana::tuple<int, char, float> ts{1, '2', 3.3f};
    hana::tuple<std::string, double> us{"foobar", 4.4};
    auto cat = ::tuple_cat(ts, us);

    assert(hana::at_c<0>(cat) == 1);
    assert(hana::at_c<1>(cat) == '2');
    assert(hana::at_c<2>(cat) == 3.3f);
    assert(hana::at_c<3>(cat) == "foobar");
    assert(hana::at_c<4>(cat) == 4.4);
}
