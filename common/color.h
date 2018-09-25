/* =============================================================================
 *   PikOS
 * ========================================================================== */

/**
 * \file color.h
 * \brief Color definitions.
 *
 * Defines the 16 colors using in VGA mode. A macro to combine foreground and
 * background colors is also provided.
 *
 * \author Anthony Mercer
 *
 */

#ifndef COLOR_H
#define COLOR_H

#define BLACK 0x00
#define BLUE 0x01
#define GREEN 0x02
#define CYAN 0x03
#define RED 0x04
#define MAGENTA 0x05
#define ORANGE 0x06
#define GREY_LIGHT 0x07
#define GREY_DARK 0x08
#define BLUE_PASTEL 0x09
#define GREEN_PASTEL 0x0A
#define CYAN_PASTEL 0x0B
#define RED_PASTEL 0x0C
#define MAGENTA_PASTEL 0x0D
#define YELLOW_PASTEL 0x0E
#define WHITE 0x0F

#define COLOR(fg, bg) (uint8)((bg << 4) | fg)

#endif