
#include <cstdio>
#include "../src/memory.hpp"

using Ensemble::MemoryPool;

int main()
{
    struct SampleStruct {
        int a;
        double b;
    };

    auto mp = new MemoryPool();

    printf("Init: %s", mp->initialize(sizeof(SampleStruct), 0x100, true) ? "T" : "F");
}
