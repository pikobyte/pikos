/* =============================================================================
 *   PikOS
 *
 *   utils.c
 *
 *   Utility functions.
 *
 * ========================================================================== */

#include "utils.h"

void mem_copy(const char *source, char *dest, const uint32 nbytes) {
  uint32 i = 0;
  for (i = 0; i < nbytes; ++i) {
    *(dest + i) = *(source + i);
  }
}