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

/* =============================================================================
 * MEMORY FUNCTIONS
 * ========================================================================== */

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

/* =============================================================================
 * STRING FUNCTIONS
 * ========================================================================== */

/**
 * \desc Receives an signed integer and converts it to a string of ASCII
 * characters including minus symbol. The output is written to memory starting
 * at the received pointer and ends with null termination. The string is in
 * reverse order to must be flipped. Firstly the sign of n is found, and if is
 * negative, makes n positive. The sign is saved for later to append the minus
 * symbol. The remainder of n and 10 is the number required, and is so added to
 * ASCII 0. This occurs whilst the current character is numeric.
 */
void itostr(int32 n, char *str) {
  uint32 i = 0;
  int32 sign = n;

  n = (sign < 0) ? -n : n;

  do {
    str[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);

  if (sign < 0) {
    str[i++] = '-';
  }
  str[i] = '\0';

  strrev(str);
}

/**
 * /desc Iterate through the string from beginning to end and end to beginning
 * simutaneously swapping str[0] with str[n], str[1] with str[n - 1] etc. Note
 * that we do not consider the null termination character: we most certainly do
 * not want to put that at the start of the string.
 */
void strrev(char *str) {
  uint32 temp = 0, i = 0, j = 0;
  for (i = 0, j = strlen(str) - 1; i < j; i++, j--) {
    temp = str[i];
    str[i] = str[j];
    str[j] = temp;
  }
}

/**
 * \desc Loops through the characters within a string, ending when the null
 * terminator is found. For every valid character, the output result is
 * incremented.
 */
uint32 strlen(const char *str) {
  uint32 i = 0;
  while (str[i] != '\0') {
    ++i;
  }
  return i;
}