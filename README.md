[![Actions Status](https://github.com/willdaplum/plumbot/workflows/MacOS/badge.svg)](https://github.com/willdaplum/plumbot/actions)
[![Actions Status](https://github.com/willdaplum/plumbot/workflows/Windows/badge.svg)](https://github.com/willdaplum/plumbot/actions)
[![Actions Status](https://github.com/willdaplum/plumbot/workflows/Ubuntu/badge.svg)](https://github.com/willdaplum/plumbot/actions)
[![Actions Status](https://github.com/willdaplum/plumbot/workflows/Style/badge.svg)](https://github.com/willdaplum/plumbot/actions)
[![Actions Status](https://github.com/willdaplum/plumbot/workflows/Install/badge.svg)](https://github.com/willdaplum/plumbot/actions) 
[![codecov](https://codecov.io/gh/willdaplum/plumbot/graph/badge.svg?token=P5ZVCTNV4X)](https://codecov.io/gh/willdaplum/plumbot)

# Plumbot

Plumbot is a custom chess engine written in C++. Interact with the command line program using UCI, or challenge me on lichess: https://lichess.org/@/plumbot

## Usage

### Build and run the standalone target

Use the following command to build and run the executable target.

```bash
cmake -S standalone -B build/standalone
cmake --build build/standalone
./build/standalone/Plumbot --help
```

### Build and run test suite

Use the following commands from the project's root directory to run the test suite.

```bash
cmake -S test -B build/test
cmake --build build/test
CTEST_OUTPUT_ON_FAILURE=1 cmake --build build/test --target test

# or simply call the executable: 
./build/test/PlumbotTests
```

To collect code coverage information, run CMake with the `-DENABLE_TEST_COVERAGE=1` option.

### Run clang-format

Use the following commands from the project's root directory to check and fix C++ and CMake source style.
This requires _clang-format_, _cmake-format_ and _pyyaml_ to be installed on the current system.

```bash
cmake -S test -B build/test

# view changes
cmake --build build/test --target format

# apply changes
cmake --build build/test --target fix-format
```

See [Format.cmake](https://github.com/TheLartians/Format.cmake) for details.
These dependencies can be easily installed using pip.

```bash
pip install clang-format==14.0.6 cmake_format==0.6.11 pyyaml
```

### Build the documentation

The documentation is automatically built and [published](https://thelartians.github.io/ModernCppStarter) whenever a [GitHub Release](https://help.github.com/en/github/administering-a-repository/managing-releases-in-a-repository) is created.
To manually build documentation, call the following command.

```bash
cmake -S documentation -B build/doc
cmake --build build/doc --target GenerateDocs
# view the docs
open build/doc/doxygen/html/index.html
```

To build the documentation locally, you will need Doxygen, jinja2 and Pygments installed on your system.

### Build everything at once

The project also includes an `all` directory that allows building all targets at the same time.
This is useful during development, as it exposes all subprojects to your IDE and avoids redundant builds of the library.

```bash
cmake -S all -B build
cmake --build build

# run tests
./build/test/PlumbotTests
# format code
cmake --build build --target fix-format
# run standalone
./build/standalone/Plumbot --help
# build docs
cmake --build build --target GenerateDocs
```
