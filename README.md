# Prefresh

Prefresh is a dynamic library loading framework designed to facilitate the development and testing of modular applications in C++. It allows for easy loading, unloading, and symbol resolution of shared libraries at runtime.

## Features

- **Dynamic Library Loading**: Load shared libraries at runtime without recompiling the entire application.C
- **Symbol Resolution**: Access functions and variables in the loaded libraries using simple function calls.
- **Modular Architecture**: Easily integrate new functionality by adding new shared libraries.
- **Debug and Release Configurations**: Build the project in both debug and release configurations.
- **Cross-Platform Support**: Currently it works only on linux and OS X.

## Getting Started

### Prerequisites

- C++ compiler (GCC, Clang, MSVC)
- CMake (for build configuration)
- Premake5 (for project generation)
- Git (for version control)

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/deathstroke18/Prefresh.git
   cd Prefresh

2. Generate the build files using Premake5:
    premake5 gmake2

3. Build the project:
    make config=Release

### Usage

1. Include the header file in your project:
    #include "Prefresh.h"

2. Load a shared library and call its functions:
    
    TestModule::LoadLibrary();
    TestModule::Foo(42);
    int value = TestModule::GetBar();

### Running Tests

To run tests, you can build the PrefreshTest target:
    make PrefreshTest config=Release

Then execute the test binary:
    ./bin/Release/PrefreshTest

### Contributing

Contributions are welcome! Please fork the repository and submit a pull request for any enhancements or bug fixes.

1. Fork the project
2. Create your feature branch (git checkout -b feature/YourFeature)
3. Commit your changes (git commit -m 'Add some feature')
4. Push to the branch (git push origin feature/YourFeature)
5. Open a pull request