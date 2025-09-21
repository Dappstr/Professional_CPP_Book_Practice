#include <iostream>
#include <utility>
#include <vector>
#include <print>

class Base {
    public:
        virtual void foo() = 0;
        virtual void bar() = 0;

    virtual ~Base() = default;
};

class DerivedOne : virtual public Base {
    public:
        void foo() override {
            std::cout << "foo" << '\n';
        }
        ~DerivedOne() override = default;
};

class DerivedTwo : virtual public Base {
    public:
        void bar() override {
            std::cout << "bar" << '\n';
        }
        ~DerivedTwo() override = default;
};

class DerivedDerived : public DerivedOne, public DerivedTwo {
    public:
        void derived() {
            std::cout << "derived" << '\n';
        }
        ~DerivedDerived() override = default;
};

void useUp(const std::unique_ptr<DerivedDerived> &derived) {
    derived->foo();
    derived->bar();
    derived->derived();
}

class Dog {
    public:
        virtual ~Dog() = default;

        virtual void bark() { std::println("Woof!"); }
        virtual void eat() { std::println("The dog ate."); }
};

class Bird {
    public:
        virtual ~Bird() = default;

        virtual void chirp() { std::println("Chirp!"); }
        virtual void eat() { std::println("The bird ate."); }
};

class DogBird final : public Dog, public Bird {};

class BaseOne {
    public:
        virtual void someFunc() { std::println("Base someFunc"); }
        virtual ~BaseOne() = default;
};

class DerivedOneOne final : public BaseOne {
    public:
        void someFunc() override { std::println("Derived someFunc"); }

        void callSomeFunc() {
            BaseOne::someFunc();
        }
        ~DerivedOneOne() override = default;
};

class Anml {
    private:
        double m_weight {0.0};

    public:
        explicit Anml(double weight) : m_weight(weight) {}
        virtual ~Anml() = default;
        virtual double getWeight() const { return m_weight; }

    protected:
        Anml() = default;
};

// ERROR PRONE! Two objects of `Anml` are being constructed from Dg and Brd when DgBrd is made
// class Dg : public virtual Anml {
//     private:
//         std::string m_name;
//     public:
//         explicit Dg(double weight, std::string name)
//             :Anml(weight), m_name(name) {}
// };
//
// class Brd : public virtual Anml {
//     private:
//         bool m_canfly {false};
//     public:
//         explicit Brd(double weight, bool canfly)
//             :Anml(weight), m_canfly(canfly) {}
// };
//
// class DgBrd final : public Dg, public Brd
// {
//     public:
//         explicit DgBrd(double weight, std::string name, bool canfly)
//             :Dg(weight, name), Brd(weight, canfly) {}
// };


class Dg : public virtual Anml {
private:
    std::string m_name;
    
    public:
        explicit Dg(double weight, std::string name)
            :Anml(weight), m_name(std::move(name)) {}
    protected:
        Dg(std::string name) : m_name(std::move(name)) {};
};

class Brd : public virtual Anml {
    private:
        bool m_canfly {false};
    
    public:
        explicit Brd(const double weight, bool canfly)
            :Anml(weight), m_canfly(canfly) {}

    protected:
        explicit Brd(bool canfly) : m_canfly(canfly) {};
};

class DgBrd final : public Dg, public Brd {
    public:
        explicit DgBrd(const double weight, std::string name, bool canfly)
            :Anml(weight), Dg(std::move(name)), Brd(canfly) {}
};


int main() {
    DerivedDerived derived;
    useUp(std::make_unique<DerivedDerived>(derived));

    std::vector<std::reference_wrapper<Base>> toDownCast;
    toDownCast.emplace_back(derived);

    dynamic_cast<DerivedOne &>(toDownCast[0].get()).foo();

    DogBird confusedAnimal {};
    // confusedAnimal.eat();    AMBIGUOUS

    dynamic_cast<Dog &>(confusedAnimal).eat(); // UP CAST
    dynamic_cast<Bird &>(confusedAnimal).eat(); // UP CAST

    // confusedAnimal.Dog::bark(); disambiguation syntax

    DerivedOneOne derivedOneOne;
    derivedOneOne.callSomeFunc();

    const DgBrd dogBrd {22.33, "Bella", true};
    std::println("Weight: {}", dogBrd.getWeight());

    return 0;
}