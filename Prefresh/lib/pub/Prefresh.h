#pragma once

#include <dlfcn.h>

void* Load(const char* filepath);

void* LoadSymbol(void* library, const char* symbol);

void Reload(void* &library, const char* filepath);

void PrintError();