#include <iostream>

// Concept to require that a given type has a non-throwing destructor and a non-throwing `swap()` method.
template <typename T>
concept C = requires (T x, T y) {
    { x.~T()} noexcept;
    { x.swap(y) } noexcept;
};

// Concept to require 'a' and 'b' to be comparable
template <typename T>
concept C2 = requires (T a, T b) {
    { a == b } -> std::convertible_to<bool>;
};

int main() {
    return 0;
}