/* =============================================================================
 *   PikOS
 *
 *   kernel.c
 *
 *   Main entry point for PikOS.
 *
 * ========================================================================== */

#include "definitions.h"
#include "screen.h"
#include "utils.h"

void main() {
  clear_screen();
  print("PikOS");
}