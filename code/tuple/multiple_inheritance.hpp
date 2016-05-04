// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#ifndef TUPLE_MULTIPLE_INHERITANCE_HPP
#define TUPLE_MULTIPLE_INHERITANCE_HPP

#include <cstddef>
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

template <>
struct tuple<> { };
// end-sample


// sample(get)
template <std::size_t n, typename T>
constexpr T& get(element<n, T>& t) {
    return t.value_;
}
// end-sample

#endif
