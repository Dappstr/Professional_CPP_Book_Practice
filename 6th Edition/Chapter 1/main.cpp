#include <cmath>
#include <iostream>
#include <utility>
#include <print>

struct S {
    std::string s;

    constexpr explicit S(std::string s) : s(std::move(s)) {}
    constexpr std::weak_ordering operator<=>(const S& other) const {
        return s <=> other.s;
    }
};

int main() {
    constexpr int a = 10;

    if (constexpr std::strong_ordering result = a <=> 10; result == std::strong_ordering::equal) { std::println("Equal"); }
    else if (result == std::strong_ordering::less) { std::println("Less"); }
    else { std::println("Greater"); }

    const double b = std::nan("Not a number");
    if (const std::partial_ordering result = b <=> 10; result == std::partial_ordering::unordered) { std::println("Unordered"); }
    else {
        if (result == std::partial_ordering::less) { std::println("Less"); }
        else { std::println("Greater"); }
    }

    const S s1("Hello world"), s2("hello world!");
    if (const auto result = s1 <=> s2; result == std::weak_ordering::less) {
        std::println("Less");
    }

    std::pair my_pair {"Test", 1337};
    auto& [str, val] {my_pair}; // Decompose

    str = "Testing";
    std::cout << my_pair.first << '\n';

    return 0;
}