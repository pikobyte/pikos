/* =============================================================================
 *   PikOS
 *
 *   kernel.c
 *
 *   Main entry point for PikOS.
 *
 * ========================================================================== */

#include "../common/definitions.h"
#include "../drivers/screen.h"
#include "../kernel/utils.h"

void main() {
  clear_screen();
  print("PikOS");
}