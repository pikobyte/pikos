/* =============================================================================
 *   PikOS
 * ========================================================================== */

/**
 * \file screen.c
 * \brief Screen function implementation.
 *
 * \author Anthony Mercer
 *
 */

#include "screen.h"

/*------------------------------------------------------------------------------
 * FUNCTION PROTOTYPES
 * ---------------------------------------------------------------------------*/
static int32 print_char(const uint8 character, const int32 x, int32 y,
                        uint8 attrib_byte);
static int32 get_screen_offset(const int32 x, const int32 y);
static int32 get_offset_x(const int32 offset);
static int32 get_offset_y(const int32 offset);
static int32 get_cursor_offset();
static void set_cursor_offset(int32 offset);
static int32 handle_scrolling(int32 offset);

/*------------------------------------------------------------------------------
 * PUBLIC API FUNCTIONS
 * ---------------------------------------------------------------------------*/

/**
 * \desc Prints a string at a given location on the screen. If both of the
 * positions are negative, then the string is written to the cursor position.
 * Single character printing is relegated to the print_char() function.
 */
void print_at(const char *str, int32 x, int32 y) {
  int32 i = 0;
  int32 offset = 0;

  /* Set cursor if x/y are negative */
  if (x >= 0 && y >= 0) {
    offset = get_screen_offset(x, y);
  } else {
    offset = get_cursor_offset();
    x = get_offset_x(offset);
    y = get_offset_y(offset);
  }

  while (str[i] != 0) {
    offset = print_char(str[i++], x, y, WHITE_ON_BLACK);
    x = get_offset_x(offset);
    y = get_offset_y(offset);
  }
}

/**
 * \desc Prints a given string at the cursor location. This function is a
 * wrapper to the print_at() function, passing in a negative position.
 */
void print(const char *str) { print_at(str, -1, -1); }

/**
 * \desc Sets the cursor back by two positions and prints a space via the
 * print_char() function. This mimics a destructive backspace (ASCII 0x08).
 */
void print_bs(void) {
  int32 offset = get_cursor_offset() - 2;
  uint32 x = get_offset_x(offset);
  uint32 y = get_offset_y(offset);
  print_char(ASCII_BS, x, y, WHITE_ON_BLACK);
}

/**
 * \desc Gets the current cursor position and prints the number of spaces a tab
 * (ASCII 0x09) is configured to using the print_char() function.
 */
void print_tab(void) {
  int32 offset = get_cursor_offset();
  uint32 x = get_offset_x(offset);
  uint32 y = get_offset_y(offset);
  print_char(ASCII_TAB, x, y, WHITE_ON_BLACK);
}

/**
 * \desc Gets the current cursor position and calls print_char() which
 * consequently increments the row by 1. This mimics a newline/feed line
 * (ASCII 0x0A).
 * */
void print_ln(void) {
  int32 offset = get_cursor_offset();
  uint32 x = get_offset_x(offset);
  uint32 y = get_offset_y(offset);
  print_char(ASCII_LN, x, y, WHITE_ON_BLACK);
}

/**
 * \desc Clears the screen by looping over the screen buffer and replacing all
 * characters with a space.
 */
void clear_screen(void) {
  uint32 i = 0;

  uint8 *screen = (uint8 *)VIDEO_ADDRESS;
  for (i = 0; i < MAX_X * MAX_Y; ++i) {
    screen[i * 2] = ' ';
    screen[i * 2 + 1] = WHITE_ON_BLACK;
  }
  set_cursor_offset(get_screen_offset(0, 0));
}

/*------------------------------------------------------------------------------
 * PRIVATE STATIC FUNCTIONS
 * ---------------------------------------------------------------------------*/

/**
 * \brief Prints a single character to the screen at some location
 *
 * \desc A provided character is printed to the screen at the given position
 * provided this position lies within the screen buffer, defined by MAX_X
 * and MAX_Y. If the position is negative, the character is printed at
 * the cursor position. A newline character increments the row. If the
 * character is not an escape sequence, the video memory/cursor position
 * offset is increased. Scrolling of the screen is handled through the
 * handle_scrolling() function.
 *
 * \param [in] character The character to be printed.
 * \param [in] x The x-position of the character.
 * \param [in] y The y-position of the character.
 * \param [in] attr The color attribute of the character, default to black
 * on white.
 *
 * \returns Position of the cursor/position in video memory.
 */
static int32 print_char(const uint8 character, const int32 x, int32 y,
                        uint8 attr) {
  int32 offset = 0;
  uint8 *vid_mem = (uint8 *)VIDEO_ADDRESS;

  if (!attr) {
    attr = WHITE_ON_BLACK;
  }

  if (x >= MAX_X || y >= MAX_Y) {
    return get_screen_offset(x, y);
  }

  if (x >= 0 && y >= 0) {
    offset = get_screen_offset(x, y);
  } else {
    offset = get_cursor_offset();
  }

  if (character == ASCII_LN) {
    y = get_offset_y(offset);
    offset = get_screen_offset(0, y + 1);
  } else if (character == ASCII_BS) {
    vid_mem[offset] = ' ';
    vid_mem[offset + 1] = attr;
  } else if (character == ASCII_TAB) {
    uint32 i = 0;
    for (i = 0; i < TAB_SIZE; ++i) {
      vid_mem[offset] = ' ';
      vid_mem[offset + 1] = attr;
      offset += 2;
    }
  } else {
    vid_mem[offset] = character;
    vid_mem[offset + 1] = attr;
    offset += 2;
  }

  offset = handle_scrolling(offset);

  set_cursor_offset(offset);
  return offset;
}

/**
 * \brief Gets the current position in video memory.
 *
 * \desc Given a position on the screen, this function returns the number of
 * bytes into the video memory. The multiplication by 2 exists as characters are
 * 2 bytes long.
 *
 * \param [in] x The desired x-position.
 * \param [in] y The desired y-position
 *
 * \returns The corresponding position in video memory.
 */
static int32 get_screen_offset(const int32 x, const int32 y) {
  return 2 * (y * MAX_X + x);
}

/**
 * \brief Gets the screen x from a given position in video memory.
 *
 * \param [in] offset The current position in video memory.
 *
 * \returns The corresponding screen x.
 */
static int32 get_offset_x(const int32 offset) {
  return (offset - (get_offset_y(offset) * 2 * MAX_X)) / 2;
}

/**
 * \brief Gets the screen y from a given position in video memory.
 *
 * \param [in] offset The current position in video memory.
 *
 * \returns The corresponding screen y.
 */
static int32 get_offset_y(const int32 offset) { return offset / (2 * MAX_X); }

/**
 * \brief Gets the cursor position via the video port.
 *
 * \desc The current position of the cursor can be retrieved through querying
 * the video port. The data 14 and 15 access the low and high 8-bits of the
 * position respectively, which is consequently read in. The two bytes are
 * concatenated into a single int and returned in character units.
 *
 * \param None.
 *
 * \returns The current cursor position.
 */
static int32 get_cursor_offset() {
  int32 offset = 0;

  port_byte_out(REG_SCREEN_CTRL, 14);
  offset = port_byte_in(REG_SCREEN_DATA) << 8;
  port_byte_out(REG_SCREEN_CTRL, 15);
  offset += port_byte_in(REG_SCREEN_DATA);

  return offset * 2;
}

/**
 * \brief Sets the cursor position via the video port.
 *
 * \desc The current position of the cursor can be set through querying
 * the video port. The data 14 and 15 accesses the low and high 8-bits of the
 * position respectively. This function sends out the current position of the
 * cursor in, splitting into low and high bytes respectively.
 *
 * \param [in] offset The current cursor position.
 *
 * \returns None.
 */
static void set_cursor_offset(int32 offset) {
  offset /= 2;
  port_byte_out(REG_SCREEN_CTRL, 14);
  port_byte_out(REG_SCREEN_DATA, (uint8)(offset >> 8));
  port_byte_out(REG_SCREEN_CTRL, 15);
  port_byte_out(REG_SCREEN_DATA, (uint8)(offset & 0xff));
}

/**
 * \brief Scrolls the screen if required.
 *
 * \desc The function checks if the current position is within the screen, and
 * returns it if it is. If not, each row is moved backward using mem_copy() and
 * utilising the fact that we know where the video memory is and how far into
 * it we are. The last line is removed and the cursor position is set back a
 * row and is returned.
 *
 * \param [in] offset The current position in video memory.
 *
 * \returns The new position in video memory.
 */
static int32 handle_scrolling(int32 offset) {
  int32 i = 0;
  char *last_line = (char *)get_screen_offset(0, MAX_Y - 1) + VIDEO_ADDRESS;

  if (offset < MAX_Y * MAX_X * 2) {
    return offset;
  }

  for (i = 1; i < MAX_Y; ++i) {
    mem_copy((char *)(get_screen_offset(0, i)) + VIDEO_ADDRESS,
             (char *)(get_screen_offset(0, i - 1)) + VIDEO_ADDRESS, MAX_X * 2);
  }

  for (i = 0; i < MAX_X * 2; ++i) {
    last_line[i] = 0;
  }

  offset -= 2 * MAX_X;
  return offset;
}