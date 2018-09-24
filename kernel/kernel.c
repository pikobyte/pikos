/* =============================================================================
 *   PikOS
 * ========================================================================== */

/**
 * \file kernel.c
 * \brief Contains the main entry point for the PikOS kernel.
 *
 * The main function is the first call after control has been given to the
 * kernel from the boot sector. From here, the operating system runs in C with
 * some assembly functionality.
 *
 * \author Anthony Mercer
 * 
 */

#include "../drivers/screen.h"
#include "../cpu/isr.h"

/**
 *
 * \brief The main entry point for the kernel.
 *
 * Currently clears the screen, prints the operating system name. and sets up
 * interrupt handling. 
 *
 * \param None.
 * \return None.
 */
void main() {
  clear_screen();
  print("PikOS");
  interrupt_install();
}