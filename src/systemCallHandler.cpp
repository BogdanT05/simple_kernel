#include "../lib/hw.h"
#include "../h/MemoryAllocator.h"
enum {
    MEM_ALLOC = 0x01,
    MEM_FREE = 0x02
};

// Realizuje sistemske pozive, poziva ga trap.S
extern "C" size_t syscallHandler(size_t code, size_t arg1) {
    if (code == MEM_ALLOC) {
        return (size_t)MemoryAllocator::getInstance().allocate(arg1);
    }

    if (code == MEM_FREE) {
        return (size_t)MemoryAllocator::getInstance().free((void*)arg1);
    }

    return 0;
}



