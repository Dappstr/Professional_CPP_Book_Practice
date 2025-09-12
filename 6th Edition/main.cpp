#include <iostream>
#include <vector>

// Template constraint to allow only array containers which also only have arithmetic members.
template <typename T>
concept isValidArray = requires {
    typename T::value_type; // Only containers will contain this member.
} && std::is_arithmetic_v<typename T::value_type>;

template <isValidArray T>
void doStuffWithArray(const T& arr) {
    for (const auto& element : arr) {
        std::cout << element << '\n';
    }
}

int main() {
    const std::vector vec = { 1, 2, 3, 4, 5 };
    constexpr std::array<std::string_view, 5> arr = {"One", "Two", "Three", "Four", "Five"};

    doStuffWithArray(vec);
    // doStuffWithArray(arr); ERROR due to constraints.

    return 0;
}
