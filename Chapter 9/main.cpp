#include <cstddef>
#include <iostream>

class Foo {
    mutable size_t m_i {}; // Can be modified in const methods
    friend class Bar; // Bar will have access to Foo's private and protected members
};

auto f() {
    int obj1, obj2;
    return obj1 > obj2 ? obj1 : obj2; // Not in the form "return object;" so the compiler cannot apply (N)RVO, instead a copy constructor is used
}

int main() {
    
}
