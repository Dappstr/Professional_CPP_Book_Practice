#include <iostream>
#include <set>
#include <span>

class C {
    public:
        C() = default;
        void mf() {
            auto lam1 = [this]() {}; // Captures the current object
            auto lam2 = [*this]() {}; // Captures a COPY of the current object
        }
        ~C() = default;

};

int main() {
    // Transparent comparator
    // Implements utilization of the greater than operator for types other than int.
    std::set<int, std::less<>> numbers1 {1, 3, 5, 7};
    std::set<int, std::greater<>> numbers2 {1, 3, 5, 7};

    // Works because without std::greater,
    //auto it = numbers.find(3.0);
    for (int x : numbers1) { // Will go in normal ascending order
        std::cout << x << ' ';
    }
    std::cout << '\n';
    for (int x : numbers2) { // Will go in descending order
        std::cout << x << ' ';
    }
    std::cout << '\n';

    // TEMPLATE LAMBDAS
    [[maybe_unused]] auto template_lambda = [] <typename T> (const std::span<T>& t) {
        // ...
    };

    return 0;
}