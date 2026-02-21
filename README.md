# L-Language

An LLVM-based programming language written in C++. Later this language shall be bootstrapped.

## Build

Link LLVM via brew or parameter. Check CMakeLists.txt.

```bash
cmake -S . -B build
cmake --build build
./build/ll
