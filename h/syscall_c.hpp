#ifndef PROJECT_SYSCALL_C_HPP
#define PROJECT_SYSCALL_C_HPP
#include "../lib/hw.h"

void* mem_alloc (size_t size);

int mem_free (void* addr);

#endif //PROJECT_SYSCALL_C_HPP
