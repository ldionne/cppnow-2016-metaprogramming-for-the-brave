// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#ifndef TUPLE_CAT_STD_HPP
#define TUPLE_CAT_STD_HPP

#include <boost/hana/at.hpp>
#include <boost/hana/tuple.hpp>

#include <cstddef>
#include <tuple>
#include <type_traits>
#include <utility>


//
// Implementation adapted from libc++
//

template <typename Tuple>
struct tuple_size;

template <typename ...T>
struct tuple_size<boost::hana::tuple<T...>> {
    static constexpr auto value = sizeof...(T);
};

template <std::size_t n, typename Tuple>
struct tuple_element;

template <std::size_t n, typename ...T>
struct tuple_element<n, boost::hana::tuple<T...>> {
    using type = typename std::tuple_element_t<n, std::tuple<T...>>::type;
};

template <typename ...T>
boost::hana::tuple<T&&...> forward_as_tuple(T&& ...t) {
    return {static_cast<T&&>(t)...};
}

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



// sample(tuple_cat_impl-1)
template <typename Types, typename Is, typename Js>
struct tuple_cat_impl;

template <typename ...T, size_t ...I, size_t ...J>
struct tuple_cat_impl<boost::hana::tuple<T...>,
                      std::index_sequence<I...>,
                      std::index_sequence<J...>>
{
    template <typename Tuple0>
    constexpr auto operator()(boost::hana::tuple<T...> t, Tuple0&& t0)
    {
        return ::forward_as_tuple(
            std::forward<T>(boost::hana::at_c<I>(t))...,
            boost::hana::at_c<J>(std::forward<Tuple0>(t0))...
        );
    }
// end-sample

// sample(tuple_cat_impl-2)
    template <typename Tuple0, typename Tuple1, typename ...Tuples>
    constexpr auto operator()(boost::hana::tuple<T...> t,
                              Tuple0&& t0, Tuple1&& t1,
                              Tuples&& ...tpls)
    {
        using T0 = std::remove_reference_t<Tuple0>;
        using T1 = std::remove_reference_t<Tuple1>;
        return tuple_cat_impl<
            boost::hana::tuple<T...,
                typename apply_cv<Tuple0,
                    typename tuple_element<J, T0>::type
                >::type&&...
            >,
            std::make_index_sequence<sizeof ...(T) +
                                     tuple_size<T0>::value>,
            std::make_index_sequence<tuple_size<T1>::value>
        >{}(
            ::forward_as_tuple(
                std::forward<T>(boost::hana::at_c<I>(t))...,
                boost::hana::at_c<J>(std::forward<Tuple0>(t0))...
            ),
            std::forward<Tuple1>(t1), std::forward<Tuples>(tpls)...
        );
    }
};
// end-sample

// sample(tuple_cat)
constexpr boost::hana::tuple<> tuple_cat() {
    return boost::hana::tuple<>();
}

template <typename Tuple0, typename ...Tuples>
constexpr auto tuple_cat(Tuple0&& t0, Tuples&& ...tpls) {
    using T0 = std::remove_reference_t<Tuple0>;
    return tuple_cat_impl<
        boost::hana::tuple<>,
        std::index_sequence<>,
        std::make_index_sequence<tuple_size<T0>::value>
    >{}(
        boost::hana::tuple<>{},
        std::forward<Tuple0>(t0),
        std::forward<Tuples>(tpls)...
    );
}
// end-sample

#endif
