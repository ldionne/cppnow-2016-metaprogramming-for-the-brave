// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#include <cassert>
#include <string>

#include "multiple_inheritance.hpp"


int main() {
    // Default construction
    {
        using Storage = tuple<int, char, std::string, double>;
        Storage storage{};
        assert(get<0>(storage) == int{});
        assert(get<1>(storage) == char{});
        assert(get<2>(storage) == std::string{});
        assert(get<3>(storage) == double{});
    }

    // Variadic construction
    {
        using Storage = tuple<int, char, std::string, double>;
        Storage storage{1, 'x', "abcdef", 3.4};
        assert(get<0>(storage) == 1);
        assert(get<1>(storage) == 'x');
        assert(get<2>(storage) == "abcdef");
        assert(get<3>(storage) == 3.4);
    }
}
