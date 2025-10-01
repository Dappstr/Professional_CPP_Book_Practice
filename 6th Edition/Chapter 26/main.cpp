#include <iostream>
template <int F>
struct Factorial {
    static constexpr int value = F * Factorial<F - 1>::value;
};
template <>
struct Factorial<0> {
    static constexpr int value = 1;
};

template <int I>
struct Loop {
    template <typename Func>
    static void run(Func f) {
        f(I);
        Loop<I - 1>::run(f);
    }
};

template<>
struct Loop<0> {
    template <typename Func>
    static void run(Func f) {}
};

void doWork(int i) {
    std::println("doWork({})", i);
}

// Check if `doIt()` exists for a type
template <typename T>
void callDoIt(const T& t) {
    if constexpr (requires { t.doIt(); }) {
        t.doIt();
    } else {
        std::println(std::cerr, "Call doIt() failed.");
    }
}

int main() {
    std::println("{}", Factorial<5>::value); // 120

    Loop<3>::run(doWork);
    return 0;
}