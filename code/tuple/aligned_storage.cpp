// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <new>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>


struct uninitialized { };

template <std::size_t n, typename ...T>
struct nth_type;

template <typename T, typename ...U>
struct nth_type<0, T, U...> {
    using type = T;
};

template <std::size_t n, typename T, typename ...U>
struct nth_type<n, T, U...> {
    using type = typename nth_type<n-1, U...>::type;
};

// sample(offsets)
template <typename ...T>
struct tuple {
    using SizeArray = std::array<std::size_t, sizeof...(T)>;
    static constexpr SizeArray sizes = {{sizeof(T)...}};
    static constexpr SizeArray alignments = {{alignof(T)...}};
// end-sample

    static constexpr SizeArray compute_offsets() {
        SizeArray offsets{};
        SizeArray const& const_offsets = static_cast<SizeArray const&>(offsets);
        std::size_t* out = &const_cast<std::size_t&>(const_offsets[0]);
        *out++ = 0;
        for (std::size_t i = 1; i < sizeof...(T); ++i) {
            // Pad the current member so it is placed at an offset
            // which is a multiple of its alignment.
            *out++ = const_offsets[i-1] + sizes[i-1] +
                         ((const_offsets[i-1] + sizes[i-1]) % alignments[i]);
        }

        return offsets;
    }

// sample(offsets)
    static constexpr SizeArray offsets = compute_offsets(); // ...
// end-sample

// sample(aligned_storage)
    static constexpr std::size_t total_size = offsets[sizeof...(T)-1] +
                                              sizes[sizeof...(T)-1];

    typename std::aligned_storage<total_size>::type storage_;
// end-sample

// sample(get_raw)
    constexpr void* get_raw(std::size_t i) {
        if (i >= sizeof...(T))
            throw "out of bounds access in a tuple";
        return ((char*)&storage_) + offsets[i];
    }
// end-sample

    explicit constexpr tuple(uninitialized&&) { }
    explicit constexpr tuple(uninitialized const&) { }

// sample(default_ctor)
    tuple() {
        std::size_t i = 0;
        void* expand[] = {::new (this->get_raw(i++)) T()...};
        (void)expand;
    }
// end-sample

// sample(variadic_ctor)
    explicit tuple(T const& ...args) {
        std::size_t i = 0;
        void* expand[] = {::new (this->get_raw(i++)) T(args)...};
        (void)expand;
    }
// end-sample

// sample(dtor)
    ~tuple() {
        std::size_t i = 0;
        int expand[] = {
            (static_cast<T*>(this->get_raw(i++))->~T(), int{})...
        };
        (void)expand;
    }
};
// end-sample

template <typename ...T>
constexpr std::array<std::size_t, sizeof...(T)> tuple<T...>::offsets;

template <>
struct tuple<> {
    constexpr tuple() { }

    template <bool always_false = false>
    constexpr auto get_raw(std::size_t) {
        static_assert(always_false,
        "tuple::get_raw must not be called on an empty tuple, because "
        "that would be an out-of-bounds access");
    }
};

// sample(get)
template <std::size_t i, typename ...T,
    typename Nth = typename nth_type<i, T...>::type>
constexpr Nth& get(tuple<T...>& ts) {
    return *static_cast<Nth*>(ts.get_raw(i));
}
// end-sample

int main() {
    // Default construction
    {
        using Storage = tuple<int, char, std::string, double>;
        Storage storage{};
        assert(get<0>(storage) == int{});
        assert(get<1>(storage) == char{});
        assert(get<2>(storage) == std::string{});
        assert(get<3>(storage) == double{});
    }

    // Variadic construction
    {
        using Storage = tuple<int, char, std::string, double>;
        Storage storage{1, 'x', "abcdef", 3.4};
        assert(get<0>(storage) == 1);
        assert(get<1>(storage) == 'x');
        assert(get<2>(storage) == "abcdef");
        assert(get<3>(storage) == 3.4);
    }

    // The addresses returned by get_raw should all be different
    {
        auto all_unique = [](auto* ...x) {
            std::vector<void*> addresses = {x...};
            std::sort(addresses.begin(), addresses.end());
            return std::adjacent_find(addresses.begin(), addresses.end()) == addresses.end();
        };

        tuple<int, char> x2{};
        assert(all_unique(x2.get_raw(0), x2.get_raw(1)));

        tuple<int, char, std::string> x3{};
        assert(all_unique(x3.get_raw(0), x3.get_raw(1), x3.get_raw(2)));
    }
}
