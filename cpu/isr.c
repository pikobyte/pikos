/* =============================================================================
 *   PikOS
 * ========================================================================== */

/**
 * \file isr.h
 * \brief Interrupt service routine handling implementation.
 *
 * \author Anthony Mercer
 *
 */

#include "isr.h"

/* Declare some handler functions for the IRQs */
ISR interrupt_handlers[256];

/* List of exception messages */
char *exception_msgs[] = {"Division By Zero ",
                          "Debug",
                          "Non Maskable Interrupt",
                          "Breakpoint",
                          "Into Detected Overflow",
                          "Out of Bounds",
                          "Invalid Opcode",
                          "No Coprocessor",

                          "Double Fault",
                          "Co-processor Segment Overrun",
                          "Bad TSS",
                          "Segment Not Present",
                          "Stack Fault",
                          "General Protection Fault",
                          "Page Fault",
                          "Unknown Interrupt",

                          "Co-processor Fault",
                          "Alignment Check",
                          "Machine Check",
                          "Reserved",
                          "Reserved",
                          "Reserved",
                          "Reserved",
                          "Reserved",

                          "Reserved",
                          "Reserved",
                          "Reserved",
                          "Reserved",
                          "Reserved",
                          "Reserved",
                          "Reserved",
                          "Reserved"};

/**
 * \desc Populate the interrupt descriptor table with the gates defined in the
 * interrupt.asm routine. Then remap the programmable interrupt controller and
 * set the interrupt request. Finally, load the table.
 */
void interrupt_install(void) {
  /* Install the interrupt service routines */
  set_idt_gate(0, (uint32)isr0);
  set_idt_gate(1, (uint32)isr1);
  set_idt_gate(2, (uint32)isr2);
  set_idt_gate(3, (uint32)isr3);
  set_idt_gate(4, (uint32)isr4);
  set_idt_gate(5, (uint32)isr5);
  set_idt_gate(6, (uint32)isr6);
  set_idt_gate(7, (uint32)isr7);
  set_idt_gate(8, (uint32)isr8);
  set_idt_gate(9, (uint32)isr9);
  set_idt_gate(10, (uint32)isr10);
  set_idt_gate(11, (uint32)isr11);
  set_idt_gate(12, (uint32)isr12);
  set_idt_gate(13, (uint32)isr13);
  set_idt_gate(14, (uint32)isr14);
  set_idt_gate(15, (uint32)isr15);
  set_idt_gate(16, (uint32)isr16);
  set_idt_gate(17, (uint32)isr17);
  set_idt_gate(18, (uint32)isr18);
  set_idt_gate(19, (uint32)isr19);
  set_idt_gate(20, (uint32)isr20);
  set_idt_gate(21, (uint32)isr21);
  set_idt_gate(22, (uint32)isr22);
  set_idt_gate(23, (uint32)isr23);
  set_idt_gate(24, (uint32)isr24);
  set_idt_gate(25, (uint32)isr25);
  set_idt_gate(26, (uint32)isr26);
  set_idt_gate(27, (uint32)isr27);
  set_idt_gate(28, (uint32)isr28);
  set_idt_gate(29, (uint32)isr29);
  set_idt_gate(30, (uint32)isr30);
  set_idt_gate(31, (uint32)isr31);

  /* Remap the programmable interrupt controller */
  port_byte_out(0x20, 0x11);
  port_byte_out(0xA0, 0x11);
  port_byte_out(0x21, 0x20);
  port_byte_out(0xA1, 0x28);
  port_byte_out(0x21, 0x04);
  port_byte_out(0xA1, 0x02);
  port_byte_out(0x21, 0x01);
  port_byte_out(0xA1, 0x01);
  port_byte_out(0x21, 0x0);
  port_byte_out(0xA1, 0x0);

  /* Install the interrupt requests */
  set_idt_gate(32, (uint32)irq0);
  set_idt_gate(33, (uint32)irq1);
  set_idt_gate(34, (uint32)irq2);
  set_idt_gate(35, (uint32)irq3);
  set_idt_gate(36, (uint32)irq4);
  set_idt_gate(37, (uint32)irq5);
  set_idt_gate(38, (uint32)irq6);
  set_idt_gate(39, (uint32)irq7);
  set_idt_gate(40, (uint32)irq8);
  set_idt_gate(41, (uint32)irq9);
  set_idt_gate(42, (uint32)irq10);
  set_idt_gate(43, (uint32)irq11);
  set_idt_gate(44, (uint32)irq12);
  set_idt_gate(45, (uint32)irq13);
  set_idt_gate(46, (uint32)irq14);
  set_idt_gate(47, (uint32)irq15);

  set_idt();
}

/**
 * \desc An interrupt is identified through the Register interrupt number. We
 * can handle each interrupt therefore individually.
 */
void isr_handler(const Registers regs) {
  char num[3] = {0};
  print("Received interrupt: ");
  itostr(regs.int_no, num);
  print(num);
  print("\n");
  print(exception_msgs[regs.int_no]);
  print("\n");
}

/**
 * \desc An interrupt request is identified through the Register interrupt
 * number. We handle each request using the interrupt service routine function
 * pointer, which runs the installed function (e.g. keyboard input). Before this
 * however, we must send an end of interrupt signal to the programmable
 * interrupt controller, otherwise it will still think we are still within an
 * interrupt and will not send anymore. If the request is >= 40 (>= the 8th
 * absolute IRQ) then we must also inform the secondary slave PIC (I/O port
 * 0x0A).
 */
void irq_handler(const Registers regs) {
  if (regs.int_no >= 40) {
    port_byte_out(0xA0, 0x20);
  }
  port_byte_out(0x20, 0x20);

  if (interrupt_handlers[regs.int_no] != 0) {
    ISR handler = interrupt_handlers[regs.int_no];
    handler(regs);
  }
}

/**
 * \desc Installs a function to an index in the handler_functions array. The
 * indices will typically be IRQ0, IRQ1 etc. The installed handler function is
 * general, dealing with timing, keyboard input etc.
 */
void reg_interrupt_handler(const uint8 n, const ISR handler) {
  interrupt_handlers[n] = handler;
}