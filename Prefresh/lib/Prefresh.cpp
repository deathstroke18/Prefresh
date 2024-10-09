#include "pub/Prefresh.h"
#include <cstdio>

void* Load(const char* filepath)
{
	return dlopen(filepath, RTLD_NOW);
}

void* LoadSymbol(void* library, const char* symbol)
{
	return dlsym(library, symbol);
}

void Reload(void* &library, const char* filepath)
{
	dlclose(library);
	library = dlopen(filepath, RTLD_NOW);
}

void PrintError()
{
	printf("Error : %s\n", dlerror());
}