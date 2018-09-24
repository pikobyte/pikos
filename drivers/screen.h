/* =============================================================================
 *   PikOS
 * ========================================================================== */

/**
 * \file screen.h
 * \brief Screen function implementation.
 *
 * \author Anthony Mercer
 *
 */

#ifndef SCREEN_H
#define SCREEN_H

#include "../common/definitions.h"
#include "../common/utils.h"
#include "../drivers/ports.h"

/* Video memory and screen buffer constants */
#define VIDEO_ADDRESS 0xb8000
#define MAX_X 80
#define MAX_Y 25
#define WHITE_ON_BLACK 0x0f

/* Screen device I/O ports */
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

/**
 * \brief Clears the screen.
 * \param None.
 * \returns None.
 */
void clear_screen(void);

/**
 * \brief Prints a string to a location on screen.
 * \param [in] str The string to be printed.
 * \param [in] x The x-position of the string.
 * \param [in] y The y-position of the string.
 * \returns None.
 */
void print_at(const char *str, int32 x, int32 y);

/**
 * \brief Prints a string at the cursor location.
 * \param [in] str The string to be printed.
 * \returns None.
 */
void print(const char *str);

#endif