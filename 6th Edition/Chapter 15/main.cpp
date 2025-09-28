#include <iostream>
#include <vector>

class C {
    private:
        std::vector<std::tuple<int, std::string, double>> m_vec {};

    public:
        C(const int x, const std::string& s, const double d)
            :m_vec {std::make_tuple(x, s, d)} {}

        std::tuple<int, std::string, double>& operator[](const size_t i) {
            return m_vec[i];
        }
};

int main() {
    C c {1, "a", 3.5};
    auto [x, s, d] = c[0];
    std::cout << x << " " << s << " " << d << '\n';
    return 0;
}