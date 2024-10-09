#include "Prefresh.h"
#include <iostream>

#ifdef DEBUG
const char* g_libPath = "bin/Debug/libPrefreshTest.so";
#else
const char* g_libPath = "bin/Release/libPrefreshTest.so";
#endif

void (*foo)();

int main()
{
	void* handle = Load(g_libPath);
		if (handle)
		{
			foo = reinterpret_cast<void (*)()>(LoadSymbol(handle, "foo"));
			if (!foo) {
				std::cerr << "Failed to load symbol 'foo'" << std::endl;
				PrintError();  // Print any loading errors
				return 1;
			}
			foo();

			int bar = *reinterpret_cast<int*>(LoadSymbol(handle, "bar"));
			std::cout << "bar == " << bar << std::endl;

			std::cout << "Please make some changes , recomplile and press enter" << std::flush;
			while (std::cin.get() != '\n') {}

			Reload(handle, g_libPath);

			foo = reinterpret_cast<void (*)()>(LoadSymbol(handle, "foo"));
			foo();

			bar = *reinterpret_cast<int*>(LoadSymbol(handle, "bar"));
			std::cout << "bar == " << bar << std::endl;

		}
		else
		{
			PrintError();

		}
	return 0;
}
