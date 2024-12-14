#include <iostream>

// Make a class with no inheritance capabilities
class C1 final {
    //...  
};

class P {
public:
    virtual void f() { std::cout << "P\n"; }
    void f2() { std::cout << __func__ << '\n'; }
};

class C : public P {
    void f() override { std::cout << "C\n"; }
    using P::f2;
};

int main() {
    P *c_ptr = new C; // c_ptr is of type P* which points to an object of type C
    c_ptr->f();       // Prints "C"
    c_ptr->f2();
    delete c_ptr;
}
