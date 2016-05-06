// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#include "aligned_storage.hpp"

#include <cassert>
#include <sstream>
#include <string>


template <std::size_t n, typename State, typename F, typename ...T>
struct nth_partial_sum;

template <typename State, typename F, typename T, typename ...U>
struct nth_partial_sum<0, State, F, T, U...> {
    using type = State;
};

template <typename State, typename F>
struct nth_partial_sum<0, State, F> {
    using type = State;
};

template <std::size_t n, typename State, typename F, typename T, typename ...U>
struct nth_partial_sum<n, State, F, T, U...> {
    using NewState = decltype(std::declval<F>()(std::declval<State>(), std::declval<T>()));
    using type = typename nth_partial_sum<n - 1, NewState, F, U...>::type;
};

template <std::size_t n, typename State, typename F, typename ...T>
using fold_left_nth = typename nth_partial_sum<n, State, F, T...>::type;


// sample(partial_sum_impl)
template <typename T, typename ...U, typename State, typename F,
          std::size_t ...i,
          typename Result = tuple<
              State, fold_left_nth<i, State, F, T, U...>...
          >
>
Result partial_sum_impl(tuple<T, U...> const& ts, State const& state,
                        F const& f, std::index_sequence<0, i...>)
{
    Result result{uninitialized{}};

    void* expand[] = {
        ::new (result.get_raw(0)) State(state),
        ::new (result.get_raw(i)) fold_left_nth<i, State, F, T, U...>(
            f(::get<i-1>(result), ::get<i-1>(ts))
        )...
    };
    (void)expand;

    return result;
}
// end-sample

// sample(partial_sum)
template <typename ...T, typename State, typename F>
auto partial_sum(tuple<T...> const& ts, State const& state, F const& f)
{
    return partial_sum_impl(ts, state, f,
                        std::make_index_sequence<sizeof...(T)+1>{});
}
// end-sample


int main() {
    tuple<int, std::string, char> storage{1, "abc", 'y'};
    auto result = partial_sum(storage, std::string{"xx"}, [](auto const& a, auto const& b) {
        std::ostringstream ss{};
        ss << a << b;
        return ss.str();
    });

    assert(::get<0>(result) == "xx");
    assert(::get<1>(result) == "xx1");
    assert(::get<2>(result) == "xx1abc");
    assert(::get<3>(result) == "xx1abcy");
}
