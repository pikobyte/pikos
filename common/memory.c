/* =============================================================================
 *   PikOS
 * ========================================================================== */

/**
 * \file memory.c
 * \brief Memory function implementation.
 *
 * \author Anthony Mercer
 *
 */

#include "memory.h"

/**
 * \desc Loops over a number of bytes specified, copying the memory from the
 * source address plus offset to the destination plus offset.
 */
void memcpy(const char *source, char *dest, const uint32 nbytes) {
  uint32 i = 0;
  for (i = 0; i < nbytes; ++i) {
    *(dest + i) = *(source + i);
  }
}