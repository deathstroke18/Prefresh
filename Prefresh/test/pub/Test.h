#pragma once

#include <array>
#include <utility>
#include "Prefresh.h"

// Prevent C++ name mangling for dlsym to work correctly
extern "C"
{
    void foo(int input);
    extern int bar;
}

// Export symbols using std::pair
std::array<std::pair<const char*, void*>, 2> g_exports = {
    std::make_pair("foo", nullptr),
    std::make_pair("bar", nullptr)
};

class TestModule : public PrefreshModule<TestModule, g_exports.size()>
{
public:
    TestModule() : PrefreshModule<TestModule, g_exports.size()>(g_exports) {} // Initialize base with g_exports

    static void Foo(int input)
    {
        GetInstance().Execute<0, void>(input); // Call foo with input
    }

    static int GetBar()
    {
        return *GetInstance().GetVar<1, decltype(bar)>(); // Access the bar variable
    }

protected:
    virtual const char* GetPath() const override
    {
#ifdef DEBUG
        return "bin/Debug/libPrefreshTest.so"; // Corrected to .so if you are on Linux
#else
        return "bin/Release/libPrefreshTest.so";
#endif
    }
};
