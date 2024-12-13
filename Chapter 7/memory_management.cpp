#include <cstddef>
#include <cstdlib>
#include <memory>
#include <new>
#include <iostream>

struct S {
    //...
};

void use_resource(std::weak_ptr<S> &weak_simple) {
    auto resource{weak_simple.lock()};
    if (resource) {
        std::cout << "Resource still alive.";
    } else {
        std::cout << "Resource freed.";
    }
    std::cout << '\n';
}

template <typename T, size_t N>
void double_arr(T (&arr)[N]) {
    for (size_t i = 0; i < N; ++i) {
        arr[i] *= 2;
    }
}

int main() {
    int **double_arr = new(std::nothrow) int*[3];
    for (size_t i = 0; i < 3; ++i) {
        double_arr[i] = new(std::nothrow) int[3];
    }
    for (size_t x = 0; x < 3; ++x) {
        for (size_t y = 0; y < 3; ++y) {
            double_arr[x][y] = y + 1;
        }
    }

    for (size_t x = 0; x < 3; ++x) {
        std::cout << x + 1 << ' ';
        for (size_t y = 0; y < 3; ++y) {
            std::cout << double_arr[x][y] << " ";
        }
        std::cout << '\n';
    }

    delete[] double_arr;

    auto shared_s { std::make_shared<S>() };
    std::weak_ptr<S> weak { shared_s };

    use_resource(weak);

    shared_s.reset();

    use_resource(weak);
    
    return EXIT_SUCCESS;
}
