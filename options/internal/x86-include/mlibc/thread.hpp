#pragma once

#include <stdint.h>
#include <mlibc/tcb.hpp>

namespace mlibc {

inline Tcb *get_current_tcb() {
	uintptr_t ptr;
	asm ("movl %%fs:0, %0" : "=r"(ptr));
	return reinterpret_cast<Tcb *>(ptr);
}

inline uintptr_t get_sp() {
	uintptr_t esp;
	asm ("mov %%esp, %0" : "=r"(esp));
	return esp;
}

} // namespace mlibc
