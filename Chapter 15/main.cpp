#include <iostream>
#include <span>
#include <vector>

template <typename T>
void f(std::span<const T> spn) noexcept { // Works on primitive arrays, std::array, std::vector, etc.
    auto b = spn.begin();
    for (; b != spn.end(); ++b) {
        std::cout << *b << ' ';
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    std::array arr2 = {6, 7, 8, 9, 10};
    std::vector<char> vec {'a', 'b', 'c'};
    f<int>(arr);
    f<int>(arr2);
    f<char>(vec);

    //std::cout << "Hello, World!" << std::endl;
    return 0;
}