/* void custom_abort() { */
    /* __builtin_trap(); */
/* } */

#define FNWRAP_INTERNAL_ERROR_REPORTER
#define FNWRAP_ABORT __builtin_trap

#pragma clang diagnostic ignored "-Wunused-value"

#include "fnwrap.hpp"


typedef unsigned long uint64;
static_assert(sizeof(uint64) == 8, "sizeof(uint64) != 8");


uint64 syscall(...) asm("syscall");


asm (
    ".globl syscall, _start\n"
    "syscall:\n"
    "movq %rdi, %rax\n"
    "movq %rsi, %rdi\n"
    "movq %rdx, %rsi\n"
    "movq %rcx, %rdx\n"
    "movq %r9, %r8\n"
    "syscall\n"
    "ret\n"
);



constexpr uint64 sys_write = 1, sys_exit = 60;


void write(uint64 fd, const char* buf, uint64 len) {
    syscall(sys_write, fd, buf, len);
}

void writestr(uint64 fd, const char* buf) {
    uint64 len=0;
    const char* ptr=buf;
    while (*ptr++) ++len;
    write(fd, buf, len);
}

void exit(int err) { syscall(sys_exit, (uint64)err); }


void f() { writestr(1, "Hello from f!\n"); }

FNWRAP(f,, f_w,,)


extern "C" void _start() {
    f();
    exit(0);
}
