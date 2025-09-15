# NOTES from the book

## Chapter 1

You can use std::strong_ordering with the spaceship operator to check for comparisons.

std::partial_ordering is for comparisons of floating point values.

If you implement your own spaceship operator, then std::weak_ordering is used.

In C++23, the [[assume]] attribute can be used to assume certain expressions are true, and that such expressions can be optimized to not be evaluated at runtime.

## Chapter 2 

`std::string` is not constexpr-able because it does not contain a constexpr constructor and is not a litral type. Use `std::string_view` instead.

Functions returning a string should reutnr a const reference to a `std::string` or a `std::string`, as returning an `std::string_view` if the string it refers to needs to reallocate.

`std::print` and `std::println` should be favored over `std::cout` especially for printing UTF-8 strings.

## Chapter 3

Doxygen is a tool that can parse and understand comments in C++ code and build documentation from them.

Decomposition is the technique of breaking down a problem into smaller subproblems. Functions for example, should not be 300 lines long.

Do not name variables or functions with a leading double underscore. This is reserved for the compiler.

## Chapter 4

`UML` (Unified Modeling Language) is a standard for modeling software systems. It is always a recommended strategy to model how your program will look and be developed before starting development on it. UML is a powerful tool for modeling how things work (their structure, behavior, responsibilities) and what they do (their interactions, usage scenarios, lifecycle).

 Favor abstraction when deciding how to implement a program. For example, if you implement a chess board, it would be better to implement a chess board class than simply creating an 8 x 8 array. Always favor getters and setters over direct access to the data members.
 
Be skeptical when identifying performance. An O(n^2) algorithm might actually perform better than an O(log n) algorithm on small input  sizes. Consider your likely input sizes before making a decision.

Before using libraries and frameworks, check to see where to submit issues and other support systems.

When sitting down with a new library, try writing a quick prototype.

## Chapter 5

While procedural programming is an okay paradigm, not all the time programs will be a linear sequence of events, and object-orientated programming gives you the ability to model data representation more adequately.

OOP is based on the notion that you should divide your program into not tasks, but into models of physical objects.

By building classes that have certain behaviors and defining how they interact, OOP offers a much richer mechanism for attaching code to the data on which it operates.

Do not "over classify" your programs. If something more simple can be represented by a simpler model/type (such as a char), do not use a class to represent it. Stick to what is more simple or easier to understand.

In aggregation, the aggregated objects/components can continue to live when the aggregator is destroyed. Such as in a "zoo" class, the animals can be moved to another zoo if the original one goes bankrupt.

In composition, objects composed of other objects are destroyed when the containing object is destroyed. This models a "has-a" relationship.

"Is-a" relationships are a good way to model inheritance.

When deciding between inheritance and composition, favor composition/"has-a" relationships, as "has-a" relationships are more flexible.

## Chapter 6

The key to abstraction is separating the interface from the implementation.

When designing a component, strive for high cohesion, also known as the "single responsibility principle" (SRP).

For example, a class which represents a car can have all the properties and behaviors of an engine, but instead of putting all that into the Car class, you should create a separate Engine class and include that into the Car class.

A "mixin" is (typically) a template class that provides a set of functionality to a derived class. It's called a "mixin" because it "mixes in" behavior into the base class.

Use up-to-date C++ idioms rather than C concepts. Such as `std::any` instead of `void*`.

Templates (for now) only allow for homogeneous types/data structures.

When designing code for reuse, consider the audience and follow the idea of familiarity. For example, use constructors/destructors for creating and destroying objects instead of creating arbitrary methods to do the same stuff in those methods.

It can be appropriate at times to provide multiple ways to do the same thing. However, use good judgement with this because over-application can easily lead to cluttered interfaces.

The "Interface Segregation Principle" (ISP) states that no client should be forced to depend on methods it does not use.
Split large/fat interfaces into smaller/thin interfaces.

Follow the "SOLID" principles. S(Single Responsibility Principle), O(Open/Closed Principle), L(Liskov Substitution Principle), I(Interface Segregation Principle), D(Dependency Inversion Principle).

## Chapter 7

"Automatic" variables/objects are variables that are automatically destroyed when they go out of scope, commonly the function they are declared in.

When working with manual memory management, creating a pointer to dynamic memory, the actual pointer remains on the stack and points to the allocated area of memory in the heap/free store.

When working with multidimensional dynamic arrays, you must allocate the memory directly on each "layer." Similarly, when you wish to release memory, you must loop through each layer "delete"-ing each element.

The "mark and sweep" garbage collector is a common way to implement garbage collection. With this approach, the garbage collector periodically examines every single pointer in the program and determines whether the referenced memory is still in use. If it is not, the memory is freed.

"Object pools" are another way to implement garbage collection. When you are done with an object, you "return" it to the pool. The pool then recycles the memory for future use.

`std::unique_ptr` allows you to pass a custom deleter function to the pointer.

With `std::shared_ptr` you can "alias" a pointer to a shared resource, which means you can share ownership of an object while also pointing to a specific memory location of that object.

```c++
#include <iostream>
#include <memory>

struct MyStruct {
    int a, b;
};

int main() {
    auto p = std::make_shared<MyStruct>();
    p->a = 42;
    p->b = 99;

    // Alias shared_ptr: shares ownership of `p`, but points to `p->b`
    std::shared_ptr<int> alias(p, &p->b);

    std::cout << "*alias = " << *alias << '\n';   // prints 99
}
```

