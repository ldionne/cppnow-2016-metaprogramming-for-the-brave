// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#ifndef STD_TUPLE_CAT_HPP
#define STD_TUPLE_CAT_HPP

#include <tuple>
#include <type_traits>
#include <utility>


//
// Implementation adapted from libc++
//

template <typename T, typename U>
struct apply_cv { using type = U; };

template <typename T, typename U>
struct apply_cv<T const, U> { using type = U const; };

template <typename T, typename U>
struct apply_cv<T volatile, U> { using type = U volatile; };

template <typename T, typename U>
struct apply_cv<T const volatile, U> { using type = U const volatile; };

template <typename T, typename U>
struct apply_cv<T&, U> { using type = typename apply_cv<T, U>::type&; };

template <typename T, typename U>
struct apply_cv<T&&, U> { using type = typename apply_cv<T, U>::type&&; };



// sample(std.tuple_cat)
constexpr std::tuple<> tuple_cat() {
    return std::tuple<>();
}

template <typename Types, typename Is, typename Js>
struct tuple_cat_impl;

template <typename ...T, size_t ...I, size_t ...J>
struct tuple_cat_impl<std::tuple<T...>,
                      std::index_sequence<I...>,
                      std::index_sequence<J...>>
{
    template <typename Tuple0>
    constexpr auto operator()(std::tuple<T...> t, Tuple0&& t0) {
        return std::forward_as_tuple(std::forward<T>(std::get<I>(t))...,
                                     std::get<J>(std::forward<Tuple0>(t0))...);
    }

    template <typename Tuple0, typename Tuple1, typename ...Tuples>
    constexpr auto operator()(std::tuple<T...> t, Tuple0&& t0, Tuple1&& t1, Tuples&& ...tpls) {
        using T0 = typename std::remove_reference<Tuple0>::type;
        using T1 = typename std::remove_reference<Tuple1>::type;
        return tuple_cat_impl<
            std::tuple<
                T...,
                typename apply_cv<Tuple0, typename std::tuple_element<J, T0>::type>::type&&...
            >,
            std::make_index_sequence<sizeof ...(T) + std::tuple_size<T0>::value>,
            std::make_index_sequence<std::tuple_size<T1>::value>
        >{}(
            std::forward_as_tuple(
                std::forward<T>(std::get<I>(t))...,
                std::get<J>(std::forward<Tuple0>(t0))...
            ),
            std::forward<Tuple1>(t1),
            std::forward<Tuples>(tpls)...
        );
    }
};

template <typename Tuple0, typename ...Tuples>
constexpr auto tuple_cat(Tuple0&& t0, Tuples&& ...tpls) {
    using T0 = typename std::remove_reference<Tuple0>::type;
    return tuple_cat_impl<
        std::tuple<>,
        std::index_sequence<>,
        std::make_index_sequence<std::tuple_size<T0>::value>
    >{}(
        std::tuple<>{},
        std::forward<Tuple0>(t0),
        std::forward<Tuples>(tpls)...
    );
}
// end-sample

#endif
