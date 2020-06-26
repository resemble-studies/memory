/**
 * License: MIT. See LICENSE in root directory.
 * \date 2020/06/19
 */

#pragma once

#include <afxres.h>
#include <cstdint>

namespace Ensemble {

class MemoryPool {

protected:

    class MemoryBlock* mpMemoryBlocks = nullptr;

    /**
     * Length of each structure in number of bytes.
     */
    DWORD mdwEntrySize = 0;

    /**
     * Number of structures allocated.
     */
    DWORD mdwBlockEntries = 0;

    DWORD mdwFreeEntries = 0;

    DWORD mdwMaxFreeEntries = 0;

    std::uintptr_t* mpFreeList = nullptr;

    bool mbZeroMem = false;

public:

    MemoryPool() = default;

    ~MemoryPool();

public:

    bool initialize(DWORD dwEntrySize, DWORD dwBlockEntries, bool bZero = false);

    std::uintptr_t* allocate();

    void release(const void* pEntry);

    void reset();
};

/**
 *
 */
class MemoryBlock {

    friend MemoryPool;

protected:

    std::uintptr_t* mpData = nullptr;

    MemoryBlock* mpNextBlock = nullptr;

public:

    MemoryBlock() = default;

    ~MemoryBlock();

protected:

    bool initialize(DWORD dwEntrySize, DWORD dwEntries);

public:

    std::uintptr_t* getStartingAddress();

    void setNextBlock(MemoryBlock*);
};

} // namespace Ensemble
