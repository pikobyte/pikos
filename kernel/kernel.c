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
#include "../common/color.h"
#include "../cpu/isr.h"
#include "../drivers/screen.h"

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
  //splash_screen();
  isr_install();
  irq_install();
  clear_screen();
  print_at("Hello", 4, 4, WHITE, WHITE);

  __asm__("int $2");
  __asm__("int $3");
}

/**
 * \desc Reads in the current line buffer and simply outputs it onto the next
 * line.
 */
void user_input(const char *input) {
  if (strcmp(input, "QUIT") == 0) {
    print("CPU halted!\n");
    __asm__ volatile("hlt");
  } else if (strcmp(input, "CLEAR") == 0) {
    clear_screen();
    print("\n > ");
  } else if (strcmp(input, "RESTART") == 0) {
    splash_screen();
  } else {
    print("   ");
    print(input);
    print("\n > ");
  }
}