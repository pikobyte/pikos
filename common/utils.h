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

#include "definitions.h"

/* =============================================================================
 * MEMORY FUNCTIONS
 * ========================================================================== */

/**
 * \brief Copies memory from one address range to another.
 * \param [in] source The start of the address to be copied.
 * \param [in] dest The destination for the copied bytes.
 * \param [in] nbytes The number of bytes to be copied.
 * \returns None.
 */
void mem_copy(const char *source, char *dest, const uint32 nbytes);

/* =============================================================================
 * STRING FUNCTIONS
 * ========================================================================== */

/**
 * \brief Converts an signed integer to ASCII representation.
 * \param [in] n The number to be converted.
 * \param [out] str The address in memory to start modification.
 * \returns None.
 */
void itostr(int32 n, char *str);

/**
 * \brief Reverses a whole string.
 * \param [in] The string to be reversed.
 * \returns None.
 */
void strrev(char *str);

/**
 * \brief Returns the length of a passed in string.
 * \param [in] str The string to be measured.
 * \returns The length of the string.
 */
uint32 strlen(const char *str);

#endif