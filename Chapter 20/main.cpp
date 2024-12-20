#include <iostream>
#include <algorithm>
#include <numeric>
#include <ranges>
#include <span>
#include <vector>

[[nodiscard]] size_t get_sum(const std::span<int> s) noexcept {
    return std::accumulate(s.begin(), s.end(), 0);
}

int main() {
    std::vector v = {1, 2, 3, 4};
    int arr[] = {1, 2, 3, 4, 5};
    std::cout << get_sum(v) << '\n';
    std::cout << get_sum(arr) << '\n';

    //auto it = std::find_if_not(v.begin(), v.end(), [](int i) -> bool { return i % 2 == 0; }); <- Can be simplified with ranges
    if (const auto it = std::ranges::find_if_not(v, [](int i) { return i % 2 == 0; });
        it != v.end()) {
        std::cout << "First non-even number is: " << *it << '\n';
    }
    auto v2 = v;
    //std::transform(v2.begin(), v2.end(), v2.begin(), [](int i) { return i * 2; } ); <- Can be simplified with ranges
    std::ranges::transform(v2, std::begin(v2), [](const int i) { return i * 2; });
    for (auto i : v2) {
        std::cout << i << ' ';
    }
    std::cout << '\n';

    std::vector<char> v3(5);
    std::iota(v3.begin(), v3.end(), 'a');
    for (const auto i : v3) {
        std::cout << i << ' ';
    }
    std::cout << '\n';

    return 0;
}
