#pragma once

#include <array>
#include <unordered_map>
#include <string>
#include <utility>
#include <dlfcn.h>
#include <stdexcept>
#include <iostream>

template <typename E, size_t NumSymbols>
class PrefreshModule
{
public:
    // Constructor to accept g_exports
    PrefreshModule(const std::array<std::pair<const char*, void*>, NumSymbols>& exports)
        : m_exports(exports)
    {
    }

    static void LoadLibrary() { GetInstance().Load(); }
    static void ReloadLibrary() { GetInstance().Reload(); }

protected:
    static E& GetInstance()
    {
        static E instance;
        return instance;
    }

    virtual const char* GetPath() const = 0;

    // Removed GetSymbolNames; using m_exports directly
    const std::array<std::pair<const char*, void*>, NumSymbols>& GetSymbolNames() const
    {
        return m_exports;
    }

    template <size_t Index, typename Ret, typename... Args>
    Ret Execute(Args... args)
    {
        auto symbol = m_exports[Index];
        if (symbol.second) // Check if the function pointer is valid
        {
            return reinterpret_cast<Ret(*)(Args...)>(symbol.second)(args...);
        }
        else
        {
            throw std::runtime_error(std::string("Function not found: ") + symbol.first);
        }
    }

    template <size_t Index, typename T>
    T* GetVar()
    {
        auto symbol = m_exports[Index];
        if (symbol.second)
        {
            return static_cast<T*>(symbol.second);
        }
        else
        {
            return nullptr; // Return nullptr if the variable is not found
        }
    }

private:
    void Load()
    {
        m_libHandle = dlopen(GetPath(), RTLD_NOW);
        if (!m_libHandle) {
            throw std::runtime_error("Failed to load library: " + std::string(dlerror()));
        }
        LoadSymbols();
    }

    void Reload()
    {
        if (m_libHandle) {
            dlclose(m_libHandle);
        }
        Load();
    }

    void LoadSymbols()
    {
        for (size_t i = 0; i < NumSymbols; ++i)
        {
            auto symbol_name = m_exports[i].first;
            void* addr = dlsym(m_libHandle, symbol_name);
            if (addr) {
                m_symbols[symbol_name] = addr;
                m_exports[i].second = addr; // Store the pointer in the pair
            }
            else {
                std::cerr << "Warning: Symbol " << symbol_name << " not found." << std::endl;
            }
        }
    }

    void* m_libHandle = nullptr; // Initialize to nullptr
    std::unordered_map<std::string, void*> m_symbols;
    std::array<std::pair<const char*, void*>, NumSymbols> m_exports; // Store exports
};
