// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#ifndef LOGICAL_AND_LAZY_HPP
#define LOGICAL_AND_LAZY_HPP

#include <type_traits>


// sample(main)
template <typename Condition, typename T = void>
struct lazy_enable_if
    : std::enable_if<Condition::value, T>
{ };

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
