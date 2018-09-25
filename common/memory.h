/* =============================================================================
 *   PikOS
 * ========================================================================== */

/**
 * \file utils.h
 * \brief Memory function declarations.
 *
 * ...
 *
 * \author Anthony Mercer
 *
 */

#ifndef MEMORY_H
#define MEMORY_H

#include "types.h"

/**
 * \brief Copies memory from one address range to another.
 * \param [in] source The start of the address to be copied.
 * \param [in] dest The destination for the copied bytes.
 * \param [in] nbytes The number of bytes to be copied.
 * \returns None.
 */
void memcpy(const char *source, char *dest, const uint32 nbytes);

#endif