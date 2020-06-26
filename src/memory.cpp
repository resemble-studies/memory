/**
 * License: MIT. See LICENSE in root directory.
 * \date 2020/06/26
 */

#include "memory.hpp"

namespace Ensemble {

////////////////////////////////////////////////////////////////////////////////////////////////////

MemoryPool::~MemoryPool()
{
    reset();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

bool MemoryPool::initialize(DWORD dwEntrySize, DWORD dwBlockEntries, bool bZero)
{
    mdwEntrySize = dwEntrySize;
    mdwBlockEntries = dwBlockEntries;
    mbZeroMem = bZero;

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

std::uintptr_t* MemoryPool::allocate()
{
    if (mdwFreeEntries == 0)
    {
        if (mdwMaxFreeEntries <= mdwBlockEntries)
        {
            mdwMaxFreeEntries += 2 * mdwBlockEntries;
            auto pEntries = new std::uintptr_t[mdwMaxFreeEntries];
            if (mpFreeList != nullptr)
            {
                memcpy(pEntries, mpFreeList, sizeof(*pEntries) * mdwFreeEntries);
            }
            delete[] mpFreeList;
            mpFreeList = pEntries;
        }

        auto pBlock = new MemoryBlock;
        if (mpMemoryBlocks != nullptr)
        {
            mpMemoryBlocks->setNextBlock(pBlock);
        }
        else
        {
            mpMemoryBlocks = pBlock;
        }
        pBlock->initialize(mdwEntrySize, mdwBlockEntries);

        if (mdwBlockEntries != 0)
        {
            auto pBlockData = pBlock->mpData;
            for (int i = 0; i < mdwBlockEntries; ++i)
            {
                mpFreeList[mdwFreeEntries++] = (std::uintptr_t)pBlockData;
                pBlockData = (std::uintptr_t*)((char*)pBlockData + mdwEntrySize);
            }
        }
    }

    auto pAllocatedEntry = mpFreeList[mdwFreeEntries - 1];
    if (mbZeroMem)
    {
        memset((void*)pAllocatedEntry, 0, mdwEntrySize);
    }

    return (std::uintptr_t*)pAllocatedEntry;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MemoryPool::release(const void* pEntry)
{
    mpFreeList[mdwFreeEntries++] = (std::uintptr_t)pEntry;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MemoryPool::reset()
{
    delete mpFreeList;

    if (mpMemoryBlocks != nullptr)
    {
//        delete mpMemoryBlocks->mpData;
//        delete mpMemoryBlocks->mpNextBlock;
        delete mpMemoryBlocks;
        mpMemoryBlocks = nullptr;
    }

    mpMemoryBlocks = nullptr;
    mdwFreeEntries = 0;
    mdwMaxFreeEntries = 0;
    mpFreeList = nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

MemoryBlock::~MemoryBlock()
{
    delete mpData;
    mpData = nullptr;

    delete mpNextBlock;
    mpNextBlock = nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

bool MemoryBlock::initialize(DWORD dwEntrySize, DWORD dwEntries)
{
    mpData = new std::uintptr_t[dwEntries * dwEntrySize];

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

std::uintptr_t* MemoryBlock::getStartingAddress()
{
    return mpData;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MemoryBlock::setNextBlock(MemoryBlock* pBlock)
{
    for (auto pTempBlock = mpNextBlock; pTempBlock->mpNextBlock == nullptr; pTempBlock = pTempBlock->mpNextBlock);

    mpNextBlock = pBlock;
}

} // namespace Ensemble
