#include <filesystem>
#include <iostream>
#include <format>
#include <sstream>

// Overly verbose way of implementing getting std::string value
void getReservationData() {
    std::print("Name and number of guests: ");
    std::string name;
    int partySize {};
    char ch;

    std::cin >> std::noskipws;
    while (std::cin >> ch) {
        if (isdigit(ch)) {
            std::cin.unget();       // Put the character back into stream.
            if (std::cin.fail()) {
                std::println(std::cerr, "cin.get() failed!");
            }
            break;
        }
        name += ch;
        if (std::cin) { std::cin >> partySize; }
        if (!std::cin) {
            std::println(std::cerr, "Error getting party size.");
            return;
        }
    }
}

void printAndParseStringStream() {
    std::string line;
    std::getline(std::cin, line);
    std::stringstream ss {line};
    std::string word {};
    while (ss >> word) {
        std::cout << word << '\n';
    }

}

void printDirectoryStructure(const char* path) {
    if (!std::filesystem::exists(path)) { return; }
    const std::filesystem::recursive_directory_iterator begin {path};
    const std::filesystem::recursive_directory_iterator end {};
    for (auto it = begin; it != end; ++it) {
        const std::string spacer(it.depth() * 2, ' ');

        if (auto& entry = *it; std::filesystem::is_regular_file(entry)) {
            std::println("{}File: {} ({} bytes)", spacer, entry.path().string(), entry.file_size());
        } else if (std::filesystem::is_directory(entry)) {
            std::println("{}Directory: {}", spacer, entry.path().string());
        }
    }
}

int main() {
    std::println(std::cerr, "Test cerr");
    std::cout.flush();
    if (!std::cin) {
        std::cout << "Unable to flush standard out!";
    }

    //printAndParseStringStream();

    constexpr char* path = "./";
    printDirectoryStructure(path);

    return 0;
}