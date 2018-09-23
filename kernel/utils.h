/* =============================================================================
 *   PikOS
 * ========================================================================== */

/**
 * \file utils.h
 * \brief Utility function declarations.
 *
 * All utility functions that are used by the operating system are defined here.
 * These include memory management.
 *
 * \author Anthony Mercer
 *
 */

#ifndef UTILS_H
#define UTILS_H

#include "../common/definitions.h"

/**
 * \brief Copies memory from one address range to another.
 * \param [in] source The start of the address to be copied.
 * \param [in] dest The destination for the copied bytes.
 * \param [in] nbytes The number of bytes to be copied.
 * \returns None.
 */
void mem_copy(const char *source, char *dest, const uint32 nbytes);

#endif