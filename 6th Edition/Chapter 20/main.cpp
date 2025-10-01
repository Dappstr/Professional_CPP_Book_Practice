#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <ranges>

int main() {
    const std::vector vec {1, 2, 3, 4};

    if (std::ranges::find(vec, 2) == vec.end()) { std::cout << "Not found" << '\n'; }

    auto sum = std::accumulate(vec.begin(), vec.end(), 0);
    std::println("{}", sum);

    std::vector<int> largeVec{};

    // First way
    for (const int i : std::views::iota(1, 101)) {
        largeVec.emplace_back(i);
    }

    // Second way
    std::vector<int> smallVec{};
    smallVec.resize(5);
    std::iota(std::begin(smallVec), std::end(smallVec), 5);

    std::vector toReplace {2, 4, 6};
    std::ranges::replace_if(toReplace, [](const int i) { return i % 2 == 0; }, 3);

    std::ranges::for_each(smallVec | std::views::filter([] (const int value) { return value % 2 == 0;}), [] (int& value) { value *= 10; });

    std::println("New values: {}", smallVec);

    return 0;
}
