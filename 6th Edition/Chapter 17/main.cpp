#include <iostream>
#include <iterator>
#include <ranges>
#include <vector>
#include <print>

template <typename Iter>
void iteratorTraitsTest(Iter it) {
    typename std::iterator_traits<Iter>::value_type temp;
    temp = *it;
    std::println("{}", temp);
}

template <std::input_iterator Iter>
auto myFind(Iter begin, Iter end, const typename std::iterator_traits<Iter>::value_type& value) {
    for (auto it = begin; it != end; ++it) {
        if (*it == value) { return it; }
    }
    return end;
}

int main() {

    const std::vector v{ 5, 3, 1, 4, 2 };
    using std::cbegin;  // For ADL
    iteratorTraitsTest(cbegin(v));

    using std::cend;
    const auto it = myFind(cbegin(v), cend(v), 3);
    std::println("{}", *it);

    std::vector<int> v2 { 'H', 'e', 'l', 'l', 'o' };
    for (const auto v3 { v2 | std::ranges::to<std::vector<char>>() }; const auto& x : v3) {
        std::cout << x;
    }

    std::cout << '\n';

    return 0;
}