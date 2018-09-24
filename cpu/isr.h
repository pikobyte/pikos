/* =============================================================================
 *   PikOS
 * ========================================================================== */

/**
 * \file isr.h
 * \brief Interrupt service routine declarations and handling functions.
 *
 * The interrupt services routines are run whenever the CPU encounters an
 * interrupt. Defined here are a list of 32 interrupts which will be linked to
 * the ISR via interrupt.asm. They are declared external such that they can be
 * accessed. As the interrupt requests (IRQs) are mapped to the range
 * overlapping the ISRs, we will remap them to 32-47. The programmable interrupt
 * controller (PIC) can be accessed via I/0 0x20 and 0x21 (primary master) as
 * well as 0xA0 and 0xA1 (secondary slave). When an interrupt request is
 * handled, the PIC is notified such that it can continue to handle further
 * interrupts. 0x20 and 0xA0 are command, 0x21 and 0xA1 are data.
 *
 * \author Anthony Mercer
 *
 */

#ifndef ISR_H
#define ISR_H

#include "../common/definitions.h"
#include "../common/utils.h"
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"
#include "idt.h"
#include "timer.h"

/* Interrupt service routine definitions (implemented in interrupt.asm) */
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

/* Interrupt request definitions (implemented in interrupt.asm) */
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

/* Define the new identifiers for the interrupt requests */
#define IRQ0 32
#define IRQ1 33
#define IRQ2 34
#define IRQ3 35
#define IRQ4 36
#define IRQ5 37
#define IRQ6 38
#define IRQ7 39
#define IRQ8 40
#define IRQ9 41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

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

/* Function pointer definition for handling IRQs */
typedef void (*ISR)(Registers);

/**
 * \brief Sets up the IDT and its gates as well as remapping the PIC.
 * \param None.
 * \returns None.
 */
void isr_install(void);

/**
 * \brief Handles a given interrupt.
 * \param [in] regs Pass in a set of registers.
 * \returns None.
 */
void isr_handler(const Registers regs);

/** \brief Enables interuptions and sets them up.
 * \param None.
 * \returns None.
 */
void irq_install(void);

/**
 * \brief Handles a given interrupt request.
 * \param [in] regs Pass in a set of registers.
 * \returns None.
 */
void irq_handler(const Registers regs);

/**
 * \brief Installs a handler function to the index of functions.
 * \param [in] n The index of handler functions to install.
 * \param [in] handler The function to install.
 * \returns None.
 */
void reg_interrupt_handler(const uint8 n, const ISR handler);

#endif