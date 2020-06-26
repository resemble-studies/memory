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
