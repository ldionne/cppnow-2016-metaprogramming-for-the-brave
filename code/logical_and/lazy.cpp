// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#include <type_traits>

#include "lazy.hpp"


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
