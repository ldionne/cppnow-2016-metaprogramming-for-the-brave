// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#include <cassert>
#include <cstddef>
#include <sstream>
#include <tuple>
#include <utility>


// sample(main)
template <typename ...T, typename F, std::size_t ...i>
void for_each_impl(std::tuple<T...> const& tuple, F const& f,
                   std::index_sequence<i...>)
{
    int expand[] = {0, (f(std::get<i>(tuple)), void(), 0)...};
    (void)expand;
}

template <typename ...T, typename F>
void for_each(std::tuple<T...> const& tuple, F const& f) {
    for_each_impl(tuple, f, std::make_index_sequence<sizeof...(T)>{});
}
// end-sample

int main() {
    std::tuple<int, char, float> ts{1, '2', 3.3f};
    std::ostringstream ss;
    for_each(ts, [&](auto x) {
        ss << x << ' ';
    });

    assert(ss.str() == "1 2 3.3 ");
}
