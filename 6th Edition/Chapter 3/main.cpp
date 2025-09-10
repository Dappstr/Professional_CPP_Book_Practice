#include <iostream>

// This sort function will essentially start from index 1 (the second index)
// shift elements back/to the left if it is less than the one in front/to the right of it.
template <typename T, size_t N>
void sort(std::array<T, N> &arr) {
    for (size_t i = 0; i < N; i++) {
        const auto element = arr[i];
        auto j = i;

        while (j > 0 && arr[j - 1] > element) {         // Will skip the first element
            std::swap(arr[j], arr[j - 1]);
            j--;
        }
    }
}

int main() {
    std::array arr = { 2, 1, 5, 3, 4 };
    sort(arr);
    for (const auto element : arr) { std::cout << element << ' '; }

    return 0;
}