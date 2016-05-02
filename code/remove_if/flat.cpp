// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#include <boost/hana/tuple.hpp>
namespace hana = boost::hana;

// sample(magic)

// end-sample


template <typename ...T, std::size_t ...i>
std::tuple<std::tuple_element_t<i, Tuple&&>...>
select(Tuple&& tuple, std::index_sequence<i...> const&) {
    return std::tuple<std::tuple_element_t<i, Tuple&&>...>{
        std::get<i>(static_cast<Tuple&&>(tuple))...
    };
}

// sample(remove_if)
template <typename >
auto remove_if(std::tuple<T...> const& tuple, Pred const& pred) {
    using Indices = typename magic<Pred, T...>::type;
    return select(tuple, Indices{}); // select coming handy!
}
// end-sample

int main() {

}
