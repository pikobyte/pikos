/* =============================================================================
 *   PikOS
 * ========================================================================== */

/**
 * \file utils.h
 * \brief String function declarations.
 *
 * ...
 *
 * \author Anthony Mercer
 *
 */

#ifndef STRING_H
#define STRING_H

#include "types.h"

/**
 * \brief Converts an signed integer to ASCII representation.
 * \param [in] n The number to be converted.
 * \param [out] str The address in memory to start modification.
 * \returns None.
 */
void itostr(int32 n, char *str);

/**
 * \brief Converts an hexidecimal value to ASCII representation.
 * \param [in] n The number to be converted.
 * \param [out] str The address in memory to start modification.
 * \returns None.
 */
void xtostr(int32 n, char *str);

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

/**
 * \brief Appends a character to a string.
 * \param [out] str The string to be appended to.
 * \param [in] c The character to be appened.
 * \returns None.
 */
void strapp(char *str, const char c);

/**
 * \brief Concatenates the second string to the first.
 * \param [out] s1 The string to be appended to.
 * \param [in] s2 The string to be appened.
 * \returns None.
 */
void strcat(char *s1, const char *s2);

/**
 * \brief Removes the last character of a string.
 * \param [out] str String to have last character removed.
 * \returns None.
 */
void strbs(char *str);

/**
 * \brief Compares two strings.
 * \param [in] str1 First string to compare.
 * \param [in] str2 Second string to compare.
 * \returns Negative value if s1 < s2, positive value if s1 > s2 and zero if
 * they are the same.
 */
int8 strcmp(const char *s1, const char *s2);

/**
 * \brief Clears a string.
 * \param [out] str String to clear.
 * \returns None.
 */
void strclr(char *str);

#endif