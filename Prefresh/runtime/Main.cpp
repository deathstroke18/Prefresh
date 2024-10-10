#include "Prefresh.h"
#include <iostream>
#include "Test.h"

#ifdef DEBUG
const char* g_libPath = "bin/Debug/libPrefreshTest.so";
#else
const char* g_libPath = "bin/Release/libPrefreshTest.so";
#endif

int main()
{
    try {
        TestModule::LoadLibrary();  // Load the library

        int exampleInput = 42; // Example input value for Foo
        TestModule::Foo(exampleInput); // Call the function with an integer argument
        std::cout << "bar == " << TestModule::GetBar() << std::endl;

        std::cout << "Make some changes, recompile, and press enter." << std::flush;
        while (std::cin.get() != '\n') {}

        TestModule::ReloadLibrary(); // Reload the library
        TestModule::Foo(exampleInput); // Call the function again with the same argument
        std::cout << "bar == " << TestModule::GetBar() << std::endl;

    }
    catch (const std::runtime_error& e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
    }
    return 0;
}
