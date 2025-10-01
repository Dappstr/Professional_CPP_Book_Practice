#include <iostream>
#include <tuple>

int main() {
    std::tuple<int, std::string, double> t1;
    int x {1337};
    std::string s {"Hello World"};
    double d {3.14159265359};

    std::tie(x, s, d) = t1;

    return 0;
}