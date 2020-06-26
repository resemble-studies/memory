# Ensemble Memory

A simple memory management encapsulation, reversed from Ensemble.

## Usage

```c++
struct SampleStruct {
    int a;
    double b;
};

auto mp = new MemoryPool();

printf("Init: %s", mp->initialize(sizeof(SampleStruct), 0x100, true) ? "T" : "F");
```

## Installation

Clone this repository as a module and include it into your CMake project:

```cmake
include("ensemble-memory/CMakeLists.txt")
```

After `add_executable`, add target `ENSEMBLE_MEMORY_LIB` into your executable:

```cmake
target_link_libraries(${MY_EXE} ${ENSEMBLE_MEMORY_LIB})
```
