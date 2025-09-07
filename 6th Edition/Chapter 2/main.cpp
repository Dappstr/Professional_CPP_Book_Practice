#include <charconv>
#include <iostream>
#include <vector>
#include <string_view>
#include <format>
#include <print>

int main() {
    if constexpr (constexpr std::string_view str = "Hello World!"; str.contains("Hello")) { // str.contains = C++23
        std::cout << "Hello found!";
    } else {
        std::cerr << "Hello not found!";
    }

    std::cout << '\n';

    using namespace std::string_literals;
    for (const std::vector strings = {"Hello"s, "World"s}; const auto& str : strings) {
        std::cout << str << '\n';
    }

    constexpr size_t size = 6;
    std::string str(size-1, '\0');
    constexpr int value = 12345;
    if (const auto result = std::to_chars(str.data(), str.data() + size, value, 10); result.ec == std::errc{}) {
        std::cout << str << '\n';
    }

    constexpr std::string_view s1{"First"}, s2{"Second"}, s3{"Third"};
    try {
        std::println("Second: {1}, First: {0}, Third {2}", s1, s2, s3);
    } catch (const std::format_error& e) {
        std::cerr << e.what() << '\n';
    }
    std::cout << std::format("Hello {}!", "World");

    return 0;
}
