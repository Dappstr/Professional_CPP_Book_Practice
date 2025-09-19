#include <iostream>
#include <vector>

class Foo {
    int x { 1337 };
    friend class Bar;

    void print() const {
        std::cout << x << '\n';
    }
};

class Bar {
    public:
        Bar() {
            Foo{}.print();
        }
};

class Spreadsheet {
    private:
        size_t m_rows { 0 }, m_cols { 0 };
        int** m_data { nullptr };

    public:
        Spreadsheet(size_t rows, size_t cols, const int filler) : m_rows { rows }, m_cols { cols } {
            m_data = new int*[rows];
            for (size_t i = 0; i < rows; ++i) {
                m_data[i] = new int[cols];
                for (size_t j = 0; j < cols; ++j) {
                    m_data[i][j] = filler;
                }
            }
        }

        // Old way to avoid copy elision
        Spreadsheet(const Spreadsheet& other) {
            if (this == &other) {
                return;
            }

            m_rows = other.m_rows;
            m_cols = other.m_cols;
            m_data = new int*[m_rows];
            for (size_t i = 0; i < m_rows; ++i) {
                m_data[i] = new int[m_cols];
                for (size_t j = 0; j < m_cols; ++j) {
                    m_data[i][j] = other.m_data[i][j];
                }
            }
        }

        // New way of using std::ranges::copy to avoid copy elision
        Spreadsheet& operator=(const Spreadsheet& other) {
            if (this == &other) {
                return *this;
            }

            m_rows = other.m_rows;
            m_cols = other.m_cols;
            m_data = new int*[m_rows];
            for (size_t i = 0; i < m_rows; ++i) {
                m_data[i] = new int[m_cols];
                std::ranges::copy(other.m_data[i], other.m_data[i] + m_cols, m_data[i]);
            }
            return *this;
        }

        ~Spreadsheet() {
            for (size_t i = 0; i < m_rows; ++i) {
                delete[] m_data[i];
            }
            delete[] m_data;
        }
};

void doSomething(int&& x) {
    x += 1;
    std::cout << x << '\n';
}

constexpr int doSomethingElse(int x) {
    if consteval {
        std::cout << "This is compile-time-able!\n";
        return x + 1;
    } else {
        std::cerr << "This is not compile-time-able!\n";
        return x;
    }
}

class Outer {
    private:
        int y { 36 };
    public:
        class Inner;
};

class Outer::Inner {
    int x { 42 };
    public:
        Inner() {
            std::cout << x << '\n';
            std::cout << Outer{}.y << '\n';
        }
};

// Example of the pimpl idiom or "bridge pattern"

class MyClassImpl;

class MyClass {
    public:
        MyClass();
        ~MyClass() = default;

        void doSomething() const;

    private:
        std::unique_ptr<MyClassImpl> m_pimpl;
};

class MyClassImpl {
    public:
        ~MyClassImpl() = default;
        std::vector<int> m_data {};
};

MyClass::MyClass() : m_pimpl(std::make_unique<MyClassImpl>()) {}

void MyClass::doSomething() const {
    m_pimpl->m_data.push_back(42);
}

int main() {
    [[maybe_unused]] Bar b {};

    constexpr int temp { 420 };
    doSomething(auto {temp}); // Creates a copy and retain the value if it's not moved. Unlike `std::move` which makes the variable be in a valid but unspecified state.

    std::cout << "Value: " << doSomethingElse(42) << '\n';

    Outer::Inner obj {};

    return EXIT_SUCCESS;
}
