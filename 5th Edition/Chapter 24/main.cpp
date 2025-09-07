#include <iostream>
#include <any>
#include <tuple>

int main() {
    std::any a {1};
    std::cout << std::any_cast<int>(a) << '\n';

    using namespace std::literals;
    a = "string"s;
    std::cout << std::any_cast<std::string>(a) << '\n';

    using Tuple = std::tuple<int, std::string, bool>;
    Tuple t {16, "test", true};

    std::cout << std::get<1>(t) << '\n';
    std::cout << std::tuple_size_v<Tuple> << '\n';

    // Decompose into copies
    auto [i, str, b] {t};
    std::cout << i << '\n';

    // Decompose into references
    auto &[i2, str2, b2] {t};
    i2 *= 2;

    std::cout << std::get<0>(t) << '\n';

    return 0;
}