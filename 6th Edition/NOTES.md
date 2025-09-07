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

