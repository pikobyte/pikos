/* =============================================================================
 *   PikOS
 * ========================================================================== */

/**
 * \file idt.h
 * \brief Interrupt descriptor table function declarations.
 *
 * The interrupt descriptor table structure is defined here, along with the
 * associated functions. This is the counterpart to the simpler, 16-bit real
 * mode interrupt vector table. Its structure is similar to that of the
 * global descriptor table and varies from 32-bit x86 to AMD 64-bit. The tables
 * contain either 8-byte (x86) or 16-byte (x64) entries, called gates.
 *
 * \author Anthony Mercer
 *
 */

#ifndef IDT_H
#define IDT_H

#include "../common/types.h"

/* Kernel code segment selector */
#define KERNEL_CS 0x08

/**
 * Definition for a 32-bit interrupt gate. This structure must be packed.
 */
typedef struct {
  uint16 low_offset; /**< Location bits of ISR 0-15 */
  uint16 selector;   /**< Code segment selector */
  uint8 zero;        /**< Unused, always 0 */
  /**
   * Bits 0-3: 1110 = 0x14 signifies 32 bit interrupt.
   * Bit 4: Zero for interrupt gate.
   * Bits 5-6: Privilege level.
   * Bit 7: Present interrupt.
   */
  uint8 flags;
  uint16 high_offset; /**< Location bits of ISR 16-31 */
} __attribute__((packed)) IDT_Gate;

/**
 * Definition for a pointer to an array of interrupt handlers which will be read
 * in via assembly in interrupt.asm. This structure must be packed.
 */
typedef struct {
  uint16 limit; /**< Size */
  uint32 base;  /**< Memory address */
} __attribute__((packed)) IDT_Register;

/* Define the table itself */
#define IDT_ENTRIES 256
IDT_Gate idt[IDT_ENTRIES];
IDT_Register idt_reg;

/**
 * \brief Sets an IDT gate to given location with fixed flags.
 * \param [in] n The records to set.
 * \param [in] loc The location of the interrupt service routines.
 * \returns None
 */
void set_idt_gate(const uint32 n, const uint32 loc);

/**
 * \brief Sets the IDT address, size and loads it in.
 * \param None.
 * \returns None.
 */
void set_idt(void);

#endif