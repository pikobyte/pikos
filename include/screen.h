/* =============================================================================
 *   PikOS
 *
 *   screen.h
 *
 *   Basic functionality for VGA.
 *
 * ========================================================================== */

#ifndef SCREEN_H
#define SCREEN_H

#include "definitions.h"
#include "ports.h"
#include "utils.h"

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f

/* Screen device I/O ports */
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

void clear_screen();
void print_at(const char *msg, int32 col, int32 row);
void print(const char *msg);

#endif