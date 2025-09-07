#include <iostream>
#include <iterator>
#include <ranges>
#include <vector>

template <typename B_Iter, typename E_iter>
[[nodiscard]] B_Iter my_find(B_Iter it, E_iter e, const int value) {
    while (it != e) {
        if (*it == value) {
            return it;
        }
        ++it;
    }
    return e;
}

int main() {
    std::vector v {11, 22, 33, 22, 11 };
    const auto it1 = my_find(v.begin(), v.end(), 22);
    const auto it2 = my_find(v.rbegin(), v.rend(), 22);

    if (it1 != std::end(v) && it2 != std::rend(v)) {
        std::cout << "Found value 22 at index " << std::distance(v.begin(), it1) << '\n'
                    << "And found 22 at index : " << it2.base() - v.begin() - 1 << '\n';
    }

    std::pmr::vector values {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Pass in values to ranges::views and filter by the numbers which are even.
    auto result1 { values | std::ranges::views::filter([](auto& x) { return x % 2 == 0; }) };
    for (const auto& x : result1) {
        std::cout << x << ' ';
    }
    std::cout << '\n';

    auto result2 { result1 | std::ranges::views::drop(2)}; // Do not include the first 2 elements.

    for (const auto& x : result2) {
        std::cout << x << ' ';
    }
    std::cout << '\n';

    auto result3 { result1 | std::ranges::views::reverse};
    for (const auto& x : result3) {
        std::cout << x << ' ';
    }
    std::cout << '\n';

    return 0;
}
