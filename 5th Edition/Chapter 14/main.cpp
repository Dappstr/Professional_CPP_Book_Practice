#include <exception>
#include <cstdlib>
#include <iostream>
#include <source_location>

[[noreturn]] void my_terminate() {
    std::cout << "Uncaught exception! Terminating...\n";
    std::terminate();
}

// Custom exception type with additional information
struct My_Custom_Exception final : public std::exception {
    [[nodiscard]] const char* what() const noexcept override {
        return "My_Custom_Exception\n";
    }
    virtual const std::source_location where() const noexcept {
        return std::source_location::current();
    }
};

void f(const int x) {
    if (x > 10) {
        throw My_Custom_Exception();
    } else {
        std::cout << x << '\n';
    }
}

int main() {
    try {
        f(12);
    } catch (const My_Custom_Exception& e) { // Catch the derived type directly
        std::cout << e.what();
        auto loc = e.where();
        std::cout << "Exception occurred at " << loc.file_name() << ":" << loc.line()
                  << " in function " << loc.function_name() << '\n';
    } catch (const std::exception& e) { // Fallback for other exceptions
        std::cout << "Unhandled std::exception: " << e.what() << '\n';
    }

    return EXIT_SUCCESS;
}
