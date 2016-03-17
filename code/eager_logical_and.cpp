// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#include <type_traits>


// sample(eager_logical_and)
template <bool ...b>
struct logical_and
    : std::is_same<
        logical_and<b...>,
        logical_and<(b, true)...>
    >
{ };
// end-sample

static_assert(logical_and<>::value, "");

static_assert( logical_and<true>::value, "");
static_assert(!logical_and<false>::value, "");

static_assert( logical_and<true, true>::value, "");
static_assert(!logical_and<true, false>::value, "");
static_assert(!logical_and<false, true>::value, "");
static_assert(!logical_and<false, false>::value, "");

static_assert( logical_and<true, true, true>::value, "");
static_assert(!logical_and<true, true, false>::value, "");
static_assert(!logical_and<true, false, true>::value, "");
static_assert(!logical_and<true, false, false>::value, "");
static_assert(!logical_and<false, true, true>::value, "");
static_assert(!logical_and<false, true, false>::value, "");
static_assert(!logical_and<false, false, true>::value, "");
static_assert(!logical_and<false, false, false>::value, "");

int main() { }
