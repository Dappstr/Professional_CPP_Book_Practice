# NOTES from the book

## Chapter 1

You can use std::strong_ordering with the spaceship operator to check for comparisons.

std::partial_ordering is for comparisons of floating point values.

If you implement your own spaceship operator, then std::weak_ordering is used.

In C++23, the [[assume]] attribute can be used to assume certain expressions are true, and that such expressions can be optimized to not be evaluated at runtime.

## Chapter 2 

`std::string` is not constexpr-able because it does not contain a constexpr constructor and is not a litral type. Use `std::String_view` instead.

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

OOP is based on the notion that you should divide your program inot into tasks, but into models of physical objects.

By building classes that have certain behaviors and defining how they interact, OOP offers a much richer mechanism for attaching code to the data on which it operates.

Do not "over classify" your programs. If something more simple can be represented by a simpler model/type (such as a char), do not use a class to represent it. Stick to what is more simple or easier to understand.

In aggregation, the aggregated objects/components can continue to live when the aggregator is destroyed. Such as in a "zoo" class, the animals can be moved to another zoo if the original one goes bankrupt.

In composition, objects composed of other objects are destroyed when the containing object is destroyed. This models a "has-a" relationship.

"Is-a" relationships are a good way to model inheritance.

When deciding between inheritance and composition, favor composition/"has-a" relationships, as "has-a" relationships are more flexible.

