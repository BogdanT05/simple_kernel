#ifndef PROJECT_MEMORYALLOCATOR_H
#define PROJECT_MEMORYALLOCATOR_H
#include "../lib/hw.h"

class MemoryAllocator {
public:
    static MemoryAllocator& getInstance();
    void* allocate (size_t size);
    int free (void* block);
private:
    MemoryAllocator();

    struct FreeBlock {
        size_t blockSize;
        FreeBlock* next;
    };

    FreeBlock* headFree;

    static int tryToJoin (FreeBlock* block);
};




#endif //PROJECT_MEMORYALLOCATOR_H
