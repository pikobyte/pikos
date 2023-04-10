/* =============================================================================
 *   PikOS
 * ========================================================================== */

/**
 * \file ports.c
 * \brief Port function implementation.
 *
 * \author Anthony Mercer
 *
 */

#include "ports.h"

/**
 * \desc Reads a byte from a specified port by doing the following:
 *  1. Load EDX with given port.
 *  2. Input byte into AL.
 *  3. Put value in AL into result.
 */
uint8 port_byte_in(uint16 port) {
  uint8 result = 0;
  __asm__("in %%dx, %%al" : "=a"(result) : "d"(port));
  return result;
}

/**
 * \desc Writes a byte to a specified port by doing the following:
 *  1. Load EAX with data.
 *  2. Load EDX with given port.
 *  3. Output data to the port.
 */
void port_byte_out(uint16 port, uint8 data) {
  __asm__ volatile("out %%al, %%dx" : : "a"(data), "d"(port));
}

/**
 * \desc Reads a word from a specified port by doing the following:
 *  1. Load EDX with given port.
 *  2. Input word into AL.
 *  3. Put value in AL into result.
 */
uint16 port_word_in(uint16 port) {
  uint16 result = 0;
  __asm__("in %%dx , %%ax" : "=a"(result) : "d"(port));
  return result;
}

/**
 * \desc Writes a word to a specified port by doing the following:
 *  1. Load EAX with data.
 *  2. Load EDX with given port.
 *  3. Output data to the port.
 */
void port_word_out(uint16 port, uint16 data) {
  __asm__ volatile("out %%ax , %%dx " : : "a"(data), "d"(port));
}