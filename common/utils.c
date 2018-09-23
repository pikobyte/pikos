/* =============================================================================
 *   PikOS
 * ========================================================================== */

/**
 * \file utils.c
 * \brief Utility function implementation.
 *
 * \author Anthony Mercer
 *
 */

#include "utils.h"

/**
 * \desc Loops over a number of bytes specified, copying the memory from the
 * source address plus offset to the destination plus offset.
 */
void mem_copy(const char *source, char *dest, const uint32 nbytes) {
  uint32 i = 0;
  for (i = 0; i < nbytes; ++i) {
    *(dest + i) = *(source + i);
  }
}

/**
 * \desc Receives an unsigned integer and converts it to a string of ASCII
 * characters including minus symbol. The output is written to memory starting
 * at the received pointer and ends with null termination.
 */
void itostr(int32 n, char *str) {
  uint32 i = 0;

  if (n < 0) {
    n = -n;
    str[i++] = '-';
  }
  do {
    str[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);

  str[i] = '\0';
}