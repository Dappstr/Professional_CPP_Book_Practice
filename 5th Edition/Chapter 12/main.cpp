#include <concepts>
#include <iostream>

// Concept requries that template is compatible with prefix and postfix operators
template <typename T>
concept C = requires(T t) {
    ++t; --t; t++; t--;
};

template <typename T>
concept Is_convertable_to_bool = std::convertible_to<T, bool>;

template <typename T>
requires std::derived_from<T, std::exception>
struct my_custom_exception<T> final : public std::exception {
    // ...
};

int main() {
    C auto v = 1; // We've constrained v's type to be sometime that is in lin with the concept
    std::cout << "Hello World!\n";
}
