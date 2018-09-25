/* =============================================================================
 *   PikOS
 * ========================================================================== */

/**
 * \file kernel.c
 * \brief Contains the main entry point for the PikOS kernel.
 *
 * \author Anthony Mercer
 *
 */

#include "kernel.h"
#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "../common/color.h"

/**
 *
 * \brief The main entry point for the kernel.
 *
 * Clears the screen, initialises interrupts and starts the shell.
 *
 * \param None.
 * \return None.
 */
void pikos_main(void) {
  splash_screen();
  isr_install();
  irq_install();
}

/**
 * \desc Reads in the current line buffer and simply outputs it onto the next
 * line. If QUIT is input, halt the CPU.
 */
void user_input(const char *input) {
  if (strcmp(input, "QUIT") == 0) {
    print("CPU halted!\n");
    __asm__ __volatile__("hlt");
  }
  print("   ");
  print(input);
  print("\n > ");
}