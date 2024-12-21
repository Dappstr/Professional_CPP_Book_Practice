#include <iostream>
#include <tuple>

template <unsigned char F>
class Factorial {
    public:
        static const unsigned long long value { F * Factorial<F - 1>::value };
};

// Specialization
template <>
class Factorial<0> {
    public:
        static constexpr unsigned long long value { 1 };
};

template <int I>
class Loop {
    public:
        template <typename FuncType>
        static inline void run(FuncType func) {
            Loop<I - 1>::run(func);
            func(I);
        }
};

template <>
class Loop<0> {
    public:
        template <typename FuncType>
        static inline void run(FuncType) {}
};

void do_work(const int i) { std::cout << "do_work(" << i << ")\n"; }

template <typename Tuple_Type, int N>
class Tuple_Print_Helper {
    public:
        Tuple_Print_Helper(const Tuple_Type &tup) {
            if constexpr (N > 1) {
                Tuple_Print_Helper<Tuple_Type, N - 1> tp {tup};
            }
            std::cout << std::get<N - 1>(tup) << '\n';
        }
};

template <typename T>
void tuple_print(const T& t) {
    Tuple_Print_Helper<T, std::tuple_size_v<T>> tp {t};
}

int main() {
    std::cout << Factorial<5>::value << std::endl;
    Loop<3>::run(do_work);

    using namespace std::literals;
    const std::tuple t { 167, "Testing"s, false, 2.3 };
    tuple_print(t);

    return 0;
}