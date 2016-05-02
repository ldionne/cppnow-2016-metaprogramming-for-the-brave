// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#ifndef REMOVE_IF_RECURSIVE_HPP
#define REMOVE_IF_RECURSIVE_HPP

#include <cassert>
#include <cstddef>
#include <tuple>
#include <type_traits>
#include <utility>


template <typename Tuple, std::size_t ...i>
auto select(Tuple&& tuple, std::index_sequence<i...> const&) {
    using Result = std::tuple<
        std::tuple_element_t<i, std::remove_reference_t<Tuple>>...
    >;
    return Result{std::get<i>(static_cast<Tuple&&>(tuple))...};
}


// sample(remove_if_impl-1)
struct detail {

template <typename Tuple, typename Pred>
static auto
remove_if_impl(Tuple const& tuple, Pred const& pred,
               std::index_sequence<>)
{
    return std::tuple<>{};
}
// end-sample

// sample(remove_if_impl-2)
template <typename Tuple, typename Pred, std::size_t i,
                                         std::size_t ...is>
static auto
remove_if_impl(Tuple const& tuple, Pred const& pred,
               std::index_sequence<i, is...>,
               std::enable_if_t<
                   decltype(pred(std::get<i>(tuple)))::value
               >* = nullptr)
{
    return detail::remove_if_impl(tuple, pred,
                                  std::index_sequence<is...>{});
}
// end-sample

// sample(remove_if_impl-3)
template <typename Tuple, typename Pred, std::size_t i,
                                         std::size_t ...is>
static auto
remove_if_impl(Tuple const& tuple, Pred const& pred,
               std::index_sequence<i, is...>,
               std::enable_if_t<
                   !decltype(pred(std::get<i>(tuple)))::value
               >* = nullptr)
{
    return std::tuple_cat(
        select(tuple, std::index_sequence<i>{}),
        detail::remove_if_impl(tuple, pred,
                               std::index_sequence<is...>{})
    );
}

}; // end struct detail
// end-sample


// sample(remove_if)
template <typename ...T, typename Pred>
auto remove_if(std::tuple<T...> const& tuple, Pred const& pred) {
    return detail::remove_if_impl(tuple, pred,
                          std::make_index_sequence<sizeof...(T)>{});
}
// end-sample

#endif
