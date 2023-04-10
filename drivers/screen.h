/* =============================================================================
 *   PikOS
 * ========================================================================== */

/**
 * \file screen.h
 * \brief Screen function definition.
 *
 * \author Anthony Mercer
 *
 */

#ifndef SCREEN_H
#define SCREEN_H

#include "../common/color.h"
#include "../common/types.h"
#include "../common/string.h"
#include "../common/memory.h"
#include "../cpu/ports.h"

/* Video memory and screen buffer constants */
#define VIDEO_ADDRESS 0xB8000
#define MAX_X 80
#define MAX_Y 25
#define TAB_SIZE 4

/* ASCII escape codes */
#define ASCII_BS 0x08
#define ASCII_TAB 0x09
#define ASCII_LN 0x0A

/* Screen device I/O ports */
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

/**
 * \brief Clears the screen.
 * \param None.
 * \returns None.
 */
void clear_screen(void);

/**
 * \brief Prints out the splash screen for when a shell is restarted.
 * \param None.
 * \returns None.
 */
void splash_screen(void);

/**
 * \brief Prints a string to a location on screen.
 * \param [in] str The string to be printed.
 * \param [in] x The x-position of the string.
 * \param [in] y The y-position of the string.
 * \returns None.
 */
void print_at(const char *str, int32 x, int32 y, uint8 fg, uint8 bg);

/**
 * \brief Prints a string at the cursor location.
 * \param [in] str The string to be printed.
 * \returns None.
 */
void print(const char *str);

/**
 * \brief Prints a colored string at the cursor location.
 * \param [in] str The string to be printed.
 * \param [in] fg The foreground color of the string.
 * \param [in] bg The background color of the string.
 * \returns None.
 */
void printc(const char *str, uint8 fg, uint8 bg);

/**
 * \brief Moves cursor back and prints a space.
 * \param None.
 * \returns None.
 */
void print_bs(void);

/**
 * \brief Prints the number of spaces a tab is configured to.
 * \param None.
 * \returns None.
 */
void print_tab(void);

/**
 * \brief Prints a new line.
 * \param None.
 * \returns None.
 */
void print_ln(void);

#endif