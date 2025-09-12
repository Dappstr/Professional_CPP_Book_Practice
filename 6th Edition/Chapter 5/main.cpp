#include <iostream>

class A {};

// Diamond inheritance, now both B and C will point to the same 'A' instance.
class B : virtual public A {};
class C : virtual public A {};

class D : public B, public C {};

int main() {

    return 0;
}