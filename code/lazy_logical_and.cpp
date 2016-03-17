// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

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


static_assert(logical_and<>::value, "");

static_assert( logical_and<std::true_type>::value, "");
static_assert(!logical_and<std::false_type>::value, "");

static_assert( logical_and<std::true_type, std::true_type>::value, "");
static_assert(!logical_and<std::true_type, std::false_type>::value, "");
static_assert(!logical_and<std::false_type, std::true_type>::value, "");
static_assert(!logical_and<std::false_type, std::false_type>::value, "");

static_assert( logical_and<std::true_type, std::true_type, std::true_type>::value, "");
static_assert(!logical_and<std::true_type, std::true_type, std::false_type>::value, "");
static_assert(!logical_and<std::true_type, std::false_type, std::true_type>::value, "");
static_assert(!logical_and<std::true_type, std::false_type, std::false_type>::value, "");
static_assert(!logical_and<std::false_type, std::true_type, std::true_type>::value, "");
static_assert(!logical_and<std::false_type, std::true_type, std::false_type>::value, "");
static_assert(!logical_and<std::false_type, std::false_type, std::true_type>::value, "");
static_assert(!logical_and<std::false_type, std::false_type, std::false_type>::value, "");

// Make sure it short-circuits
template <typename ...T>
struct Fails {
    static_assert(sizeof...(T) && false, "do not instantiate");
    static constexpr bool value = true;
};

static_assert( logical_and<std::true_type, std::true_type>::value, "");
static_assert(!logical_and<std::false_type, Fails<>>::value, "");
static_assert(!logical_and<std::true_type, std::false_type, Fails<>>::value, "");

int main() { }
