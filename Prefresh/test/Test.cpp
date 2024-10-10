#include <iostream>

extern "C" {
    void foo() {
        std::cout << "foo called! brufgdv" << std::endl;
    }

    int bar = 52; // Example variable
}
