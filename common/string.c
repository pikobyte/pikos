/* =============================================================================
 *   PikOS
 * ========================================================================== */

/**
 * \file string.c
 * \brief String function implementation.
 *
 * \author Anthony Mercer
 *
 */

#include "string.h"

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
 * incremented. The null terminator is not included in the count.
 */
uint32 strlen(const char *str) {
  uint32 i = 0;
  while (str[i] != '\0') {
    ++i;
  }
  return i;
}

/**
 * \desc Sets the null terminator of a string str to a passed in character c.
 * The null terminator is then put at the original string length + 1.
 */
void strapp(char *str, const char n) {
  const uint32 len = strlen(str);
  str[len] = n;
  str[len + 1] = '\0';
}

/**
 * \desc Loops through the characters in string to be concatenated (s2) and
 * appends each character to the modified string (s1).
 */
void strcat(char *s1, const char *s2) {
  uint32 i = 0;
  const uint32 len2 = strlen(s2);

  for (i = 0; i < len2; ++i) {
    strapp(s1, s2[i]);
  }
}

/**
 * \desc Finds the length of a string and sets its last valid character to the
 * null terminator.
 */
void strbs(char *s) {
  const uint32 len = strlen(s);
  s[len - 1] = '\0';
}

/**
 * \desc Loops whenever the current character of each string is equal. If the
 * null terminator is reached for each, then the strings are equal and zero is
 * returned. Otherwise return the difference between the characters that differ:
 * negative when str1 < str2 and positive when str1 > str2.
 */
int8 strcmp(const char *str1, const char *str2) {
  uint32 i = 0;
  for (i = 0; str1[i] == str2[i]; i++) {
    if (str1[i] == '\0') {
      return 0;
    }
  }
  return str1[i] - str2[i];
}