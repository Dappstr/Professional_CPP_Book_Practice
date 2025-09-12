#include <iostream>
#include <vector>

// Example of polymorphism
class Animal {
    public:
        virtual ~Animal() = default;
        Animal() = default;

        virtual void speak() = 0;
};

class Dog final : public Animal {
    public:
        void speak() override { std::cout << "Woof!\n"; }
};

class Cat final : public Animal {
    public:
        void speak() override { std::cout << "Meow!\n"; }
};

// Template constraint to allow only array containers which also only have arithmetic members.
template <typename T>
concept isValidArray = requires {
    typename T::value_type; // Only containers will contain this member.
} && std::is_arithmetic_v<typename T::value_type>;

template <isValidArray T>
void doStuffWithArray(const T& arr) {
    for (const auto& element : arr) {
        std::cout << element << '\n';
    }
}

int main() {
    const std::vector vec = { 1, 2, 3, 4, 5 };
    constexpr std::array<std::string_view, 5> arr = {"One", "Two", "Three", "Four", "Five"};

    doStuffWithArray(vec);
    // doStuffWithArray(arr); ERROR due to constraints.

    Animal* animal = new Dog();
    animal->speak();

    reinterpret_cast<Cat*>(animal)->speak(); // reinterpret_cast is used for changing pointer types.

    return 0;
}
