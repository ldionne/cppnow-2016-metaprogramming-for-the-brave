// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#include <cassert>
#include <cstddef>
#include <tuple>
#include <utility>


// sample(main)
template <typename Tuple, std::size_t ...i>
auto select(Tuple&& tuple, std::index_sequence<i...> const&) {
    using Result = std::tuple<
        std::tuple_element_t<i, std::remove_reference_t<Tuple>>...
    >;
    return Result{std::get<i>(static_cast<Tuple&&>(tuple))...};
}
// end-sample

int main() {
    long four = 4;
    std::tuple<int, char, float, long&> ts{1, '2', 3.3f, four};

    auto slice = select(ts, std::index_sequence<0, 2, 3>{});
    assert(std::get<0>(slice) == 1);
    assert(std::get<1>(slice) == 3.3f);
    assert(&std::get<2>(slice) == &four);
}
