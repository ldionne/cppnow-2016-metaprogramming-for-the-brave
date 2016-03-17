// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#ifndef EAGER_LOGICAL_AND_HPP
#define EAGER_LOGICAL_AND_HPP

#include <type_traits>


// sample(eager_logical_and)
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
