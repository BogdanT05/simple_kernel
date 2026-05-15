#include "../h/syscall_c.hpp"
#include "../h/syscallCodes.hpp"

// Wrapper funkcije koje samo izazivaju skok u prekidnu rutinu
// Iz prekidne rutine prelazi se u systemCallhandler koji zapravo realizuje sistemske pozive

static inline size_t syscall(size_t code, size_t arg1, size_t arg2 = 0, size_t arg3 = 0) {
    size_t ret;
    asm volatile(
      "mv a0, %1\n"
      "mv a1, %2\n"
      "mv a2, %3\n"
      "mv a3, %4\n"
      "ecall\n"
      "mv %0, a0\n"
      : "=r"(ret)
      : "r"(code), "r"(arg1), "r"(arg2), "r"(arg3)
      : "a0", "a1", "a2", "a3"
    );

    return ret;
}

void *mem_alloc(size_t size) {
    size = (size + MEM_BLOCK_SIZE - 1)/MEM_BLOCK_SIZE;
    return (void*)syscall(MEM_ALLOC, size);
}

int mem_free(void *addr) {
    return (int)syscall(MEM_FREE, (size_t)addr);
}
