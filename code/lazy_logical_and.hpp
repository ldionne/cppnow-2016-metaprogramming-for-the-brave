// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#ifndef LAZY_LOGICAL_AND_HPP
#define LAZY_LOGICAL_AND_HPP

#include <type_traits>


// sample(lazy_logical_and-lazy_enable_if)
template <typename Condition, typename T = void>
struct lazy_enable_if
    : std::enable_if<Condition::value, T>
{ };
// end-sample

// sample(lazy_logical_and)
std::true_type expand(...);

template <typename ...Bools>
decltype(expand(typename lazy_enable_if<Bools, int>::type{}...))
and_impl(int);

template <typename ...Bools>
std::false_type and_impl(...);

template <typename ...Bools>
struct logical_and
    : decltype(and_impl<Bools...>(int{}))
{ };
// end-sample

#endif
