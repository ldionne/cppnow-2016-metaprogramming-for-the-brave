// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#include <cassert>
#include <cstddef>
#include <string>
#include <type_traits>
#include <utility>


// sample(tuple_impl)
template <std::size_t i, typename T>
struct element {
    element() = default;
    explicit constexpr element(T const& t) : value_(t) { }
    T value_;
};

template <typename Indices, typename ...T>
struct tuple_impl;

template <std::size_t ...i, typename ...T>
struct tuple_impl<std::index_sequence<i...>, T...>
    : element<i, T>...
{
    constexpr tuple_impl() = default;

    constexpr explicit tuple_impl(T const& ...t)
        : element<i, T>(t)...
    { }
};
// end-sample


// sample(tuple)
template <typename ...T>
struct tuple
    : tuple_impl<std::make_index_sequence<sizeof...(T)>, T...>
{
    using tuple_impl<std::make_index_sequence<sizeof...(T)>,
                     T...>::tuple_impl;
};
// end-sample


// sample(get)
template <std::size_t n, typename T>
constexpr T& get(element<n, T>& t) {
    return t.value_;
}
// end-sample

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
