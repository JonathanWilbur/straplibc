/* SPDX-License-Identifier: LGPL-2.1 OR MIT */
/*
 * x86_64 specific definitions for NOLIBC
 * Copyright (C) 2017-2022 Willy Tarreau <w@1wt.eu>
 */

#ifndef _NOLIBC_ARCH_X86_64_H
#define _NOLIBC_ARCH_X86_64_H

#include "compiler.h"
#include "crt.h"
#include "stdint.h"

/* Syscalls for x86_64 :
 *   - registers are 64-bit
 *   - syscall number is passed in rax
 *   - arguments are in rdi, rsi, rdx, r10, r8, r9 respectively
 *   - the system call is performed by calling the syscall instruction
 *   - syscall return comes in rax
 *   - rcx and r11 are clobbered, others are preserved.
 *   - the arguments are cast to long and assigned into the target registers
 *     which are then simply passed as registers to the asm code, so that we
 *     don't have to experience issues with register constraints.
 *   - the syscall number is always specified last in order to allow to force
 *     some registers before (gcc refuses a %-register at the last position).
 *   - see also x86-64 ABI section A.2 AMD64 Linux Kernel Conventions, A.2.1
 *     Calling Conventions.
 *
 * Link x86-64 ABI: https://gitlab.com/x86-psABIs/x86-64-ABI/-/wikis/home
 *
 */

extern size_t syscall0(int syscall_num);
extern size_t syscall1(int syscall_num, void *a);
extern size_t syscall2(int syscall_num, void *a, void *b);
extern size_t syscall3(int syscall_num, void *a, void *b, void *c);
extern size_t syscall4(int syscall_num, void *a, void *b, void *c, void *d);
extern size_t syscall5(int syscall_num, void *a, void *b, void *c, void *d, void *e);
extern size_t syscall6(int syscall_num, void *a, void *b, void *c, void *d, void *e, void *f);

#define my_syscall0(n)                  	syscall0(n)
#define my_syscall1(n, a)               	syscall1(n, a)
#define my_syscall2(n, a, b)            	syscall2(n, a, b)
#define my_syscall3(n, a, b, c)         	syscall3(n, a, b, c)
#define my_syscall4(n, a, b, c, d)      	syscall4(n, a, b, c, d)
#define my_syscall5(n, a, b, c, d, e)   	syscall5(n, a, b, c, d, e)
#define my_syscall6(n, a, b, c, d, e, f)	syscall6(n, a, b, c, d, e, f)

/* startup code */
/*
 * x86-64 System V ABI mandates:
 * 1) %rsp must be 16-byte aligned right before the function call.
 * 2) The deepest stack frame should be zero (the %rbp).
 *
 */
__asm__ (
	".section .text\n"
	".globl _start\n"
	"_start:\n"
	"  xor  %ebp, %ebp\n" /* zero the stack frame                            */
	"  mov  %rsp, %rdi\n" /* save stack pointer to %rdi, as arg1 of _start_c */
	"  and  $-16, %rsp\n" /* %rsp must be 16-byte aligned before call        */
	"  call _start_c\n"   /* transfer to c runtime                           */
	"  hlt\n"             /* ensure it does not return                       */
);

extern void _start(size_t *sp);

#endif /* _NOLIBC_ARCH_X86_64_H */
