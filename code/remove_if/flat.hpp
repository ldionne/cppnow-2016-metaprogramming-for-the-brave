// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#ifndef REMOVE_IF_FLAT_HPP
#define REMOVE_IF_FLAT_HPP

#include <array>
#include <cstddef>
#include <tuple>
#include <utility>


namespace detail {
    template <typename InputIt, typename T>
    constexpr std::size_t
    count(InputIt first, InputIt last, T const& value) {
        std::size_t n = 0;
        for (; first != last; ++first)
            if (*first == value)
                ++n;
        return n;
    }
}

template <typename Tuple, std::size_t ...i>
auto select(Tuple&& tuple, std::index_sequence<i...> const&) {
    using Result = std::tuple<
        std::tuple_element_t<i, std::remove_reference_t<Tuple>>...
    >;
    return Result{std::get<i>(static_cast<Tuple&&>(tuple))...};
}

// sample(magic-1)
template <typename Pred, typename ...T>
struct magic {
    static constexpr bool results[] = {
        decltype(std::declval<Pred>()(std::declval<T>()))::value...
    };

    static constexpr std::size_t N_keep = detail::count(
        std::begin(results), std::end(results), false
    );
// end-sample

// sample(magic-2)
    using Indices = std::array<std::size_t, N_keep>;
    static constexpr Indices compute_indices() {
        Indices indices{};
        std::size_t* out = &const_cast<std::size_t&>(
            static_cast<Indices const&>(indices)[0]
        );
        for (std::size_t i = 0; i < sizeof...(T); ++i) {
            if (!results[i]) {
                *out++ = i;
            }
        }

        return indices;
    }

    static constexpr Indices indices = compute_indices();
// end-sample

// sample(magic-3)
    template <std::size_t ...i>
    static std::index_sequence<indices[i]...>
    as_index_sequence(std::index_sequence<i...>);

    using type = decltype(
        as_index_sequence(std::make_index_sequence<N_keep>{})
    );
}; // end struct magic
// end-sample

// sample(remove_if)
template <typename ...T, typename Pred>
auto remove_if(std::tuple<T...> const& tuple, Pred const& pred) {
    using Indices = typename magic<Pred, T...>::type;
    return select(tuple, Indices{}); // select coming handy!
}
// end-sample

#endif
