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

## Chapter 8

Starting with C++23, you can use the "explicit object parameter" feature instead of `this->

```c++
void SpreadsheetCell::setValue(this SpreadsheetCell& self, double value) {
    self.m_value = value;
    printCell(self);
}
```

"Delegating constructors" are ctors which call another ctor.

If you are deliberately allowing the ctor to convert types/values, mark it with `explicit(false)`

## Chapter 9

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

## Chapter 10

Attempting to override a non-virtual method in a base class hides the base class method and will only use the context of the derived class.

When compiling a class, a binary object is created that contains all the methods of a class. In the non-virtual case for methods, the control transfer to the appropriate member functions is hard-coded directly / a direct jump, based on the compile-time type. This is called static/early binding.

For virtual tables, when a method is called, the vtable pointer is followed and the appropriate version of the member function is executed based on the actual type of the object at run time.

Virtual methods work only on references or pointers.

`final` can be applied to methods that should not be overridden.

Calls to virtual methods from within a ctor or dtor are resolved statically at compile time.

Pure virtual methods can be implemented, but they must be implemented outside the definition of the class, and then it can be called from inside the derived class with the scope resolution operator.
```c++
class MyClass {
    public:
        virtual void doSomething() = 0;
};

void MyClass::doSomething() { std::println("MyClass::doSomething()"); }
```

When it comes to virtual methods with the same name inherited by a class, you should use upcasting to call the correct version, or use "disambiguation syntax."

When overloading the copy assignment operator or copy ctor, you should almost always copy the parent class as well.

RTTA stands for "Run Time Type Information." It is a mechanism that allows you to determine the type of an object at runtime.

The `typeid` operator strips reference and const qualifiers from the type.

## Chapter 11

Header files have a number of problems, such as avoiding multiple includes of the same header file. Additionally, simply `#include`ing `<iostream>` adds tens of thousands of lines of code that the compiler has to go through.
If several source files `#include <iostream>`, all of those translation units grow much bigger.

Modules solve these problems and more. Modules are compiled once to a binary format, which the compiler can then use whenever a module is imported in another source file.

Incremental compilation is also improved, as certain modificatiosn in modules do not trigger recompilation of users of that module and are not influenced by any externally defined macros.

`import std` is a huge improvement, allowing you to include the entire standard library in a single line, making everything available.

Modules require explicitly stating what you want to export.

Modules can be split into an interface file and implementation file.

An interface module starts with `export module <name>;` and an implementation module starts with `module <name>;`.` Module implementation files cannot export anything. Only interface modules can.

There can only be one file with a certain partition name. Having an implementation file that starts with the same partition name is ill-formed.

```c++
export module datamodel:address; // datamodel:address partition

export namespace DataModel {
class Address {
    public:
        Address();
        /* … */
    };
}
```

You can separate interface and implementation files by using `module :private;`

All translation units are compiled independently into object files.

The linker is the final phase of the compilation process. It links all the object files together into a single binary.

There are four types of linkage:
1. No linkage: The name is accessible only from the scope in which it is defined.
2. External linkage: The name is accessible from anywhere.
3. Internal linkage: The name is accessible only from within the translation unit.
4. Module linkage: The name is accessible only in any translation unit from the same module.

Entities in an anonymous namespace have internal linkage.

Static variables can often be used to remember whether a particular initialization has already been done.

The initialization order of nonlocal variables in different source files is undefined.

## Chapter 12

Templates are implemented in a two-phase lookup process. The first phase is the "template instantiation" phase, where the compiler looks for a template type of a certain name. The second phase is where code is generated depending on the type of the name.

When dealing with error debugging templates, use explicit instantiations and try to be explicit with which types you're working with.

Virtual methods are not allowed to be templated.

Some compilers do not enforce use of `this` to refer to data members and methods in a base class template. You can instead use `Base<T>::`

Use inheritance for extending implementations and for polymorphism. Use specialization for customizing implementations for particular types.

When deducing the return type of a template function without a template, you should use the trailing return type syntax for the expression you're expecting. This is because at the time of the prototype line, for example the type of `arg1 + arg2` ` is unknown.

```c++
template <typename T1, typename T2>
auto add(const T1& t1, const T2& t2) -> decltype(t1+t2) {
    return t1 + t2;
}
```

Template constrains can be combined with `&&` or can be used in either or (`||`)

## Chapter 13

When working with streams:
A call to unget() causes the stream to back up by one position, essentially putting the previous character read back on the stream.
You can use the `fail()` member function to see whether `unget()` was successful or not. For example, `unget()` can fail if the current position is at the beginning of the stream.

If you need to build up a string by concatenating several smaller strings, using a string stream will be more performant compared to concatenating string objects directly.

This for example moves to the third-to-last byte of an input stream:
`inStream.seekg(-3, ios_base::end);`

`std::fstream` is an example of a bidirectional stream.

## Chapter 14

In professionally written software, a terminate_handler is usually set up to create a crash dump before terminating the process. A crash dump usually contains information such as the call stack and local variables at the time the uncaught exception was thrown.

`noexcept` can be used as an operator utilizing an innter `noexcept` expression to determine whether a function is noexcept.

You can use `std::throw_with_nested()` to throw an exception that contains another exception.

You can use `dynamic_cast` to get access to a nested exception. If the value is `nullptr`, then there was no nested exception, the pointer is null, and the exception is null.

You can rethrow the same expression by using `throw;`

"Stack unwinding" is the process of destroying all local variables, and all code remaining in each function past the point of execution is skipped.

***WARNING*** Careless exception handling can lead to memory leaks.

Since C++20, a proper object-oriented replacement for `__func__` and these C-style preprocessor macros is available in the form of an of source:location has the following public accessors:

`file_name()` Contains the current source code filename

`function_name()` Contains the current function name, if the current position is inside a function

`line()` Contains the current line number in the source code

`column()` Contains the current column number in the source cod

C++23 introduces the `<stacktrace>` library, which provides a `std::stacktrace` class that can be used to get a stack trace of the current thread.

Any constructor that completes without an exception will cause the corresponding destructor to be run.

***Do not throw exceptions from destructors.***

## Chapter 15

Operator overloads should always, if possible, be defined as member functions rather than global functions.

## Chapter 16

`std::vector` and `std::optional` are two examples of "vocabulary types."

`mdspan` can be used for multidimensional contiguous arrays of memory.

`set` can be used when you want to store a set of unique values.

`set`, `map`, and `multimap` are all referred to as associative containers, since they associate keys and values.

You should use the container-specific member function form of an algorithm, if provided, because it is generally more efficient or appropriate for the container at hand.

## Chapter 17

Iterators must be copy-constructible, copy-assignable, and destructible. L values of iterators must be swappable.

It is recommended to use nonmember iterator functions, such as `std::begin()` and `std::end()`, instead of member functions.

By combining ADL (calling begin(…) without any namespace qualification) with the using std::begin declaration, the compiler first looks up the right overload in the namespace of the type of its argument using ADL.
If the compiler cannot find an overload using ADL, it tries to find an appropriate overload in the std namespace due to the using declaration. Just calling begin() without the using declaration would only call user-defined overloads through ADL, and just calling std::begin() would only look in the std namespace.

`std::iterator_traits<Iter>::value_type` is a way of determine the underlying type behind the iterator (like an int, std::string, etc.)

`std::advance(iter, n)` function to advance a given iterator, iter, by n positions.

For random-access iterators, it simply does iter += n. For other iterators, it does ++iter or --iter in a loop n times, depending on whether n is positive or negative.

## Chapter 18

Standard library containers use value semantics on elements. When you write classes that you intend to use with the Standard Library, you need to make sure they are copyable. When requesting an element from the container, a reference to the stored copy is returned.

If you want to remove all elements satisfying a condition, one solution would be to write a loop iterating over all the elements and erasing every element that matches the condition.
However, this solution has quadratic complexity, which is bad for performance. This quadratic complexity can be avoided by using the remove-erase-idiom, which has a linear complexity.

`shrink_to_fit()` can be used to shrink the capacity of a container to fit its size.

Use `std::bitset` instead of `std::vector<bool>` for storing boolean values.

`std::deque` are not stored in a contiguous memory block.

"Splicing" referrs to the process of inserting a container into another container. `std::list` does this in constant time.

`std::multimap` allows you to store identical key/value pairs.

## Chapter 19

For lambda expressions that do not capture anything, the compiler automatically provides a conversion operator that converts the lambda expression to a function pointer. Such lambda expressions can then, for example, be used to pass to functions that accept a function pointer as one of their arguments.

