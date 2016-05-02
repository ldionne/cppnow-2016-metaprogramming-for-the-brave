// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#include <cassert>
#include <tuple>
#include <type_traits>

#include "recursive.hpp"


int main() {
    auto is_even = [](auto i) {
        return std::integral_constant<bool,
            decltype(i)::value % 2 == 0
        >{};
    };

    auto ints = std::make_tuple(
        std::integral_constant<int, 0>{},
        std::integral_constant<int, 1>{},
        std::integral_constant<int, 2>{},
        std::integral_constant<int, 3>{},
        std::integral_constant<int, 4>{},
        std::integral_constant<int, 5>{},
        std::integral_constant<int, 6>{},
        std::integral_constant<int, 7>{}
    );

    assert(remove_if(ints, is_even) == std::make_tuple(1, 3, 5, 7));
}
