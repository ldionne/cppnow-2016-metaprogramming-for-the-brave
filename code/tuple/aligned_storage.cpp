// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

#include "aligned_storage.hpp"


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

    // The addresses returned by get_raw should all be different
    {
        auto all_unique = [](auto* ...x) {
            std::vector<void*> addresses = {x...};
            std::sort(addresses.begin(), addresses.end());
            return std::adjacent_find(addresses.begin(), addresses.end()) == addresses.end();
        };

        tuple<int, char> x2{};
        assert(all_unique(x2.get_raw(0), x2.get_raw(1)));

        tuple<int, char, std::string> x3{};
        assert(all_unique(x3.get_raw(0), x3.get_raw(1), x3.get_raw(2)));
    }
}
