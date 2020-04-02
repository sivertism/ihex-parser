IntelHexParser
==============

[![Build Status](https://travis-ci.com/sivertism/ihex-parser.svg?branch=master)](https://travis-ci.com/github/sivertism/ihex-parser)

C++ Intel Hex Parser, a utility to read executables in the [Intel Hex Format](https://en.wikipedia.org/wiki/Intel_HEX).
This repository was forked from [bstrysko/IntelHexParser](https://github.com/bstrysko/IntelHexParser) and modified to add support for Record Type 4, fix various bugs, add accessor (IntelHexFile::getProgramData) to raw entries to avoid populating entire address space (as the original IntelHexFile::getProgram does).

Installation:
=============

``` bash
git clone https://github.com/sivertism/ihex-parser.git
cd ihex-parser
mkdir build
cd build
cmake ..
make
sudo make install
```

To test that it works, you can run the example app to print the contents of a hex file

``` bash
./apps/example <path/to/a/.hex/file>
```
It should print out the start address and data content of each type 0 entry.

Including in other CMake projects:
==================================

Add the following to your `CMakeLists.txt` file:

``` cmake
find_package(ihex-parser REQUIRED)

# ...

target_link_libraries(myProject ... IntelHexParser::ihex-parser)
```

Include the header in your source `.cpp` file:

``` c++
#include <ihex-parser/IntelHexFile.hpp>
```

Usage:
======

``` c++
// ...
IntelHexFile file("path/to/file.hex");
auto programData = file.getProgramData();
// ...
```

See `apps/main.cpp` for more details.
