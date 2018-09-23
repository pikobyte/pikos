/* =============================================================================
 *   PikOS
 *
 *   ports.c
 *
 *   Basic functionality for port I/O.
 *
 * ========================================================================== */

#include "ports.h"

/*
    Reads a byte from a specified port by doing the following:
    1. Load EDX with given port
    2. Input byte into AL
    3. Put value in AL into result

    NOTE: Register syntax swapped compared to NASM.
*/
uint8 port_byte_in(const uint16 port) {
  uint8 result = 0;
  __asm__("in %%dx, %%al" : "=a"(result) : "d"(port));
  return result;
}

/*
    Writes a byte to a specified port by doing the following:
    1. Load EAX with data
    2. Load EDX with given port
    3. Output data to the port
*/
void port_byte_out(const uint16 port, const uint8 data) {
  __asm__("out %%al, %%dx" : : "a"(data), "d"(port));
}

/* Reads a word from a specified port */
uint16 port_word_in(const uint16 port) {
  uint16 result = 0;
  __asm__("in %%dx , %%ax" : "=a"(result) : "d"(port));
  return result;
}

/* Writes a word to a specified port */
void port_word_out(const uint16 port, const uint16 data) {
  __asm__("out %%ax , %%dx " : : "a"(data), "d"(port));
}