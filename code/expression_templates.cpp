// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#include <functional>
#include <iostream>
#include <string>


// sample(main)
template <typename F, typename Left, typename Right>
struct expr {
    F f; Left left; Right right;
    auto operator()() const { return f(left(), right()); }
};

template <typename Left, typename Right>
auto operator+(Left const& left, Right const& right) {
    return expr<std::plus<>, Left, Right>{std::plus<>{}, left, right};
}

template <int>
struct Leaf {
    int operator()() const { return 1; }
};

int main() {
    Leaf<1> a; Leaf<2> b; Leaf<3> c; Leaf<4> d;
    auto expr = (a + b) + (c + d);
    std::cout << expr() << std::endl;
}
// end-sample
