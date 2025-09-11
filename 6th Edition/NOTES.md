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

`UML` (Unified Modeling Language) is a standard for modeling software systems. It is always a recommended strategy to model how your progam will look and be developed before starting development on it.

 Favor abstraction when deciding how to implement a program. For example, if you implement a chess board, it would be better to implement a chess board class than simply creating an 8 x 8 array. Always favor getters and setters over direct access to the data members.
 
Be skeptical when identifying performance. An O(n^2) algorithm might actually perform better than an O(log n) algorithm on small input  sizes. Consider your likely input sizes before making a decision.

Before using libraries and frameworks, check to see where to submit issues and other support systems.

When sitting down with a new library, try writing a quick prototype.

