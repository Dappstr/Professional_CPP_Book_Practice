#include <iostream>
#include <memory>

void custom_free(int* ptr) {
    std::cout << "Custom free called with ptr: " << ptr << '\n';
    delete ptr;
}

int main() {
    int x = 1337;
    auto smrt { std::make_unique<int>(x) };
    std::cout << *smrt << '\n';

    int y = 25;
    // smrt.reset(&y); Problematic even though it does work.

    smrt = std::make_unique<int>(y); // Option 1 (BETTER)

    // smrt.reset(new int(y)); // Option 2

    std::cout << *smrt << '\n';

    const auto z = new int(420); // Will not leak since we're taking ownership of it through a `unique_ptr`

    const auto smrt2 = std::unique_ptr<int, decltype(&custom_free)>(z, &custom_free);

    std::cout << *smrt2 << '\n';

    return 0;
}