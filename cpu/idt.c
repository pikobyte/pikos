/* =============================================================================
 *   PikOS
 * ========================================================================== */

/**
 * \file idt.c
 * \brief Interrupt descriptor table function implementation.
 *
 * \author Anthony Mercer
 *
 */

#include "idt.h"

/* Define the table itself */
#define IDT_ENTRIES 256
IDT_Gate idt[IDT_ENTRIES] = {0};
IDT_Register idt_reg;

/**
 * \desc Sets n'th IDT gate values at locations of the corresponding assembly
 * functions. The selector is set to the kernel code segment of 0x08 and the
 * flags are set such that that a 32-bit interrupt is present in ring 0, i.e the
 * kernel.
 */
void set_idt_gate(uint32 n, uint32 loc) {
  idt[n].low_offset = lo16(loc);
  idt[n].selector = KERNEL_CS;
  idt[n].zero = 0;
  idt[n].flags = 0x8E; /* 0b10001110 */
  idt[n].high_offset = hi16(loc);
}

/**
 * \desc The address of the IDT is set through the base member and size is just
 * the number of entries multiplied by the size of those entries minus one. The
 * inline assembly utilises the load IDT command to load in our register.
 */
void set_idt(void) {
  idt_reg.base = (uint32)&idt;
  idt_reg.limit = IDT_ENTRIES * sizeof(IDT_Gate) - 1;
  __asm__ volatile("lidtl (%0)" : : "r"(&idt_reg));
}