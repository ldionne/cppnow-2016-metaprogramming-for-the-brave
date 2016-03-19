// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#ifndef MY_TUPLE_CAT_HPP
#define MY_TUPLE_CAT_HPP

#include <boost/hana/at.hpp>
#include <boost/hana/tuple.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>


//
// Implementation adapted from Hana
//

template <typename Tuple>
struct tuple_size;

template <typename ...T>
struct tuple_size<boost::hana::tuple<T...>> {
    static constexpr auto value = sizeof...(T);
};

template <typename ...T>
boost::hana::tuple<T&&...> forward_as_tuple(T&& ...t) {
    return {static_cast<T&&>(t)...};
}

namespace mystd {
    template <typename InputIt, typename T>
    constexpr T accumulate(InputIt first, InputIt last, T init) {
        for (; first != last; ++first)
            init += *first;
        return init;
    }

    template <typename T, std::size_t Size>
    struct array {
        T elems_[Size > 0 ? Size : 1];

        constexpr T& operator[](std::size_t n)
        { return elems_[n]; }

        constexpr T const& operator[](std::size_t n) const
        { return elems_[n]; }

        constexpr std::size_t size() const noexcept
        { return Size; }

        constexpr T* begin() noexcept             { return elems_; }
        constexpr T const* begin() const noexcept { return elems_; }
        constexpr T* end() noexcept               { return elems_ + Size; }
        constexpr T const* end() const noexcept   { return elems_ + Size; }
    };
}


// sample(my.tuple_cat)
template <std::size_t ...Lengths>
struct flatten_indices {
    static constexpr std::size_t lengths[] = {Lengths..., 0};
    static constexpr auto flat_length =
        mystd::accumulate(lengths, lengths + sizeof...(Lengths), 0);

    template <bool Inner>
    static constexpr auto compute() {
        mystd::array<std::size_t, flat_length> indices{};
        for (std::size_t index = 0, i = 0; i < sizeof...(Lengths); ++i)
            for (std::size_t j = 0; j < lengths[i]; ++j, ++index)
                indices[index] = (Inner ? i : j);
        return indices;
    }

    static constexpr auto inner = compute<true>();
    static constexpr auto outer = compute<false>();

    template <typename Tuples, std::size_t ...i>
    static constexpr auto apply(Tuples tuples, std::index_sequence<i...>) {
        return boost::hana::make_tuple(
            boost::hana::at_c<outer[i]>(boost::hana::at_c<inner[i]>(tuples))...
        );
    }
};

template <typename ...Tuples>
constexpr auto tuple_cat(Tuples&& ...tuples) {
    using Indices = flatten_indices<
        tuple_size<typename std::remove_reference<Tuples>::type>::value...
    >;
    return Indices::apply(
        ::forward_as_tuple(std::forward<Tuples>(tuples)...),
        std::make_index_sequence<Indices::flat_length>{}
    );
}
// end-sample

#endif
