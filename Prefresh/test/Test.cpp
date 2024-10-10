#include <iostream>

extern "C" {
    void foo() {
        std::cout << "function called!" << std::endl;
    }

    int bar = 52; // Example variable
}
