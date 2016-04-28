// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#ifndef LOGICAL_AND_RECURSIVE_HPP
#define LOGICAL_AND_RECURSIVE_HPP

#include <type_traits>


// sample(main)
template <typename ...Bools>
struct logical_and;

template <>
struct logical_and<> {
    static constexpr bool value = true;
};

template <typename Bool, typename ...Bools>
struct logical_and<Bool, Bools...> {
    static constexpr bool value = std::conditional<Bool::value,
                                    logical_and<Bools...>,
                                    std::false_type
                                >::type::value;
};
// end-sample

#endif
