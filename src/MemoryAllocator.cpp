#include "../h/MemoryAllocator.h"

MemoryAllocator & MemoryAllocator::getInstance() {
    // Staticka instanca se pravi samo jednom
    static auto instance = MemoryAllocator();
    return instance;
}

MemoryAllocator::MemoryAllocator() {
    headFree = (FreeBlock*) HEAP_START_ADDR;
    // Velicina se cuva u blokovima bruto (sa zaglavljem)
    headFree->blockSize = ((uint8*)HEAP_END_ADDR - (uint8*)HEAP_START_ADDR) / MEM_BLOCK_SIZE;
    headFree->next = nullptr;
}

void * MemoryAllocator::allocate(size_t size) {
    if (size <= 0) return nullptr;

    size += sizeof(FreeBlock);
    size_t blockNeeded = (size + MEM_BLOCK_SIZE - 1) / MEM_BLOCK_SIZE;

    FreeBlock * block = headFree;
    FreeBlock * prev = nullptr;

    // First fit
    for (; block != nullptr; prev = block, block = block->next)
        if (block->blockSize >= blockNeeded) break;

    if (block == nullptr) return nullptr;
    size_t remainingBlockSize = block->blockSize - blockNeeded;

    // Ako moze da se smesti header i bar jedan blok za podatke
    if (remainingBlockSize > (sizeof(FreeBlock) + MEM_BLOCK_SIZE -1) / MEM_BLOCK_SIZE + 1) {
        block->blockSize = blockNeeded;
        auto * newBlock = (FreeBlock*)((uint8*)block + blockNeeded * MEM_BLOCK_SIZE);

        if (prev != nullptr) prev->next = newBlock;
        else headFree = newBlock;

        newBlock->next = block->next;
        newBlock->blockSize = remainingBlockSize;
    }
    else {
        if (prev != nullptr) prev->next = block->next;
        else headFree = block->next;
    }

    block->next = nullptr;
    // Vraca se adresa nakon zaglavlja
    return (uint8*) block + sizeof(FreeBlock);
}

int MemoryAllocator::tryToJoin(FreeBlock *block) {
    if (block == nullptr) return 0;
    // Ako sledeci slobodan blok pocinje gde se ovaj zavrsava znaci moze da se spoji
    if (block->next != nullptr &&
        (uint8*)block + block->blockSize*MEM_BLOCK_SIZE == (uint8*)block->next) {

        block->blockSize += block->next->blockSize;
        block->next = block->next->next;
        return 1;
    }

    return 0;
}

int MemoryAllocator::free(void *block) {
    if (block == nullptr) return 0;
    // block pokazuje na memoriju koju korisnik moze da koristi, zaglavlje je pre
    auto* newBlock = (FreeBlock*)((uint8*) block - sizeof(FreeBlock));

    if ((void*)newBlock >= HEAP_END_ADDR ||
        (void*)newBlock < HEAP_START_ADDR) {
        return -1;
    }

    FreeBlock *current;
    // Ako treba pre headera
    if (headFree == nullptr || (uint8*)newBlock < (uint8*)headFree)
        current = nullptr;
    else
        // Odzavamo uredjenost liste, trazimo izmedju koja dva slobodna bloka se nalazi zauzeti
        for (current = headFree; current->next != nullptr && (uint8*)newBlock > (uint8*)current->next;
            current = current->next){}

    // Provera da li se radi dvostruki free
    if (current != nullptr && (newBlock == current || newBlock == current->next))
        return -1;

    if (current == nullptr && newBlock == headFree)
        return -1;

    if (current != nullptr) {
        newBlock->next = current->next;
        current->next = newBlock;
    }
    else {
        newBlock->next = headFree;
        headFree = newBlock;
    }

    tryToJoin(newBlock);
    tryToJoin(current);

    return 0;
}
