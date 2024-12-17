// Demystifying C++ I/O

// cin = input stream, reads data from the "input console"
// cout = buffered output stream, writes data to the "output console"
// cerr = unbuffered output stream, writes data to the "error console," which is often the same as the "output console"
// clog = buffered version of 'cerr'

#include <iostream>

int main() {
    int sum {};
    std::cout << "Enter a number on separate lines:\n";
    while (!std::cin.bad()) {
        int number {};
        std::cin >> number;
        if (std::cin.good()) {
            sum += number;
        } else if (std::cin.eof()) { // CTRL+Z on Windows
            break;
        } else if (std::cin.fail()) {
            std::cin.clear();
            std::string bad_token{};
            std::cin >> bad_token;
            std::cerr << "Bad input encountered: " << bad_token << std::endl;
        }
    }
    std::cout << sum;
    return EXIT_SUCCESS;
}