#ifndef PROJECT_MEMORYALLOCATOR_H
#define PROJECT_MEMORYALLOCATOR_H
#include "../lib/hw.h"

// Ova klasa predstavlja osnovni interfejs za rad sa memorijom
// Njene glavne metode su allocate i free
// Algoritam alokacije je First Fit

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

    // Helper funkcija za spajanje slobodnih blokova
    static int tryToJoin (FreeBlock* block);
};




#endif //PROJECT_MEMORYALLOCATOR_H
