# Chapter 9 Notes

A `friend` class does not mean that it can directly access private members. It must still require an object of the class to access them.

```c++
class Foo {
    int x { 1337 };
    friend class Bar;

    void print() {
        std::cout << x << '\n';
    }
};

class Bar {
    public:
        Bar() {
            Foo{}.print();
        }
};
```

If you seek to use a copy of an object and move it if it's explicitly moved, or otherwise keep the object the same, you can use decay-copy syntax to retain the object unless explicitly moved in the called function:
```c++
void doSomething(int&& x) {
    x += 1;
    std::cout << x << '\n';
}

    constexpr int temp { 420 };
    doSomething(auto {temp});
```

`std::exchange()` will replace the variable with a value and then return the old value.

For NRVO, even though the copy/move constructors won't be called, they still need to be accessible; otherwise, the program is ill-formed according to the standard.

The ternary operator disallows copy/move elision, and even worse creates lvalues which means the compiler uses the copy constructor. When using ternary and returning, use `std::move()` if you wish to not return a copy.

`if consteval {...}` is a C++23 feature to check if a function is able to be compile-time evaluated.

"PIMPL" (Pointer to Implementation) or the "bridge pattern" is a design pattern that allows a class to be used without exposing its implementation.

```c++
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
```