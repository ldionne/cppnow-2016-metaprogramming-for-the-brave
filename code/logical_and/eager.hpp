// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#ifndef LOGICAL_AND_EAGER_HPP
#define LOGICAL_AND_EAGER_HPP

#include <type_traits>


// sample(main)
template <bool ...> struct bools;

template <typename ...Bools>
struct logical_and
    : std::is_same<
        bools<Bools::value...>,
        bools<(Bools::value, true)...>
    >
{ };
// end-sample

#endif
