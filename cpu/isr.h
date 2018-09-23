/* =============================================================================
 *   PikOS
 * ========================================================================== */

/**
 * \file isr.h
 * \brief Interrupt service routine declarations and handling functions.
 *
 * The interrupt services routines are run whenever the CPU encounters an
 * interrupt. Defined here are a list of 32 interrupts which will be linked to
 * the ISR via interrupt.asm. They are declared external such that they can
 * be accessed.
 *
 * \author Anthony Mercer
 *
 */

#ifndef ISR_H
#define ISR_H

#include "../common/definitions.h"
#include "../common/utils.h"
#include "../drivers/screen.h"
#include "idt.h"

/* Routines reserved for CPU exceptions */
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

/**
 * Define a struct to hold a number of registers.
 */
typedef struct {
  uint32 ds; /**< Data segment selector. */
  uint32 edi, esi, ebp, esp, ebx, edx, ecx,
      eax;                             /**< General purpose registers. */
  uint32 int_no, err_code;             /**< Interrupt number and error code */
  uint32 eip, cs, eflags, useresp, ss; /**< No direct access */
} Registers;

/**
 * \brief Sets up the IDT and its gates.
 * \param None.
 * \returns None.
 */
void isr_install();

/**
 * \brief Handles a given interrupt.
 * \param [in] regs Pass in a set of registers.
 * \returns None.
 */
void isr_handler(Registers regs);

#endif