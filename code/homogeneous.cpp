// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#include <boost/hana/for_each.hpp>
#include <boost/hana/tuple.hpp>

#include <array>
namespace hana = boost::hana;


int main() {

{
// sample(tuple)
hana::tuple<int, int, int, int, int> ints{1, 2, 3, 4, 5};
int sum = 0;
hana::for_each(ints, [&](int i) { sum += i; });
// end-sample
}

{
// sample(array)
std::array<int, 5> ints{{1, 2, 3, 4, 5}};
int sum = 0;
for (int i : ints)
    sum += i;
// end-sample
}

}
