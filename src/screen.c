/* =============================================================================
 *   PikOS
 *
 *   screen.c
 *
 *   Basic functionality for VGA.
 *
 * ========================================================================== */

#include "screen.h"

/*------------------------------------------------------------------------------
 * FUNCTION PROTOTYPES
 * ---------------------------------------------------------------------------*/
static int32 print_char(const uint8 character, const int32 col, int32 row,
                        uint8 attrib_byte);
static int32 get_screen_offset(const int32 col, const int32 row);
static int32 get_offset_row(const int32 offset);
static int32 get_offset_col(const int32 offset);
static int32 get_cursor_offset();
static void set_cursor_offset(int32 offset);
static int32 handle_scrolling(int32 offset);

/*------------------------------------------------------------------------------
 * PUBLIC API FUNCTIONS
 * ---------------------------------------------------------------------------*/

/**
 * Print a message on the specified location
 * If col, row, are negative, we will use the current offset.
 */
void print_at(const char *msg, int32 col, int32 row) {
  int32 i = 0;
  int32 offset = 0;

  /* Set cursor if col/row are negative */
  if (col >= 0 && row >= 0) {
    offset = get_screen_offset(col, row);
  } else {
    offset = get_cursor_offset();
    row = get_offset_row(offset);
    col = get_offset_col(offset);
  }

  while (msg[i] != 0) {
    offset = print_char(msg[i++], col, row, WHITE_ON_BLACK);
    row = get_offset_row(offset);
    col = get_offset_col(offset);
  }
}

void print(const char *msg) { print_at(msg, 0, 0); }

/* Clears the screen with space characters and sets the cursor to the top left.
 */
void clear_screen() {
  int32 i = 0;

  uint8 *screen = (uint8 *)VIDEO_ADDRESS;
  for (i = 0; i < MAX_COLS * MAX_ROWS; ++i) {
    screen[i * 2] = ' ';
    screen[i * 2 + 1] = WHITE_ON_BLACK;
  }
  set_cursor_offset(get_screen_offset(0, 0));
}

/*------------------------------------------------------------------------------
 * PRIVATE STATIC FUNCTIONS
 * ---------------------------------------------------------------------------*/

/* Print a character at col, row or cursor position. */
static int32 print_char(const uint8 character, const int32 col, int32 row,
                        uint8 attr) {
  int32 offset = 0;

  /* Ptr to video memory */
  uint8 *vid_mem = (uint8 *)VIDEO_ADDRESS;

  /* If attr = 0, assume B&W */
  if (!attr) {
    attr = WHITE_ON_BLACK;
  }

  /* If row or col are out of bounds then return */
  if (col >= MAX_COLS || row >= MAX_ROWS) {
    return get_screen_offset(col, row);
  }

  /* If a row and col are > 0, that is our offset, otherwise use the cursor
   * position */
  if (col >= 0 && row >= 0) {
    offset = get_screen_offset(col, row);
  } else {
    offset = get_cursor_offset();
  }

  /* If the input character is a newline, set the offset to the end of the row.
   * Then the next character will be on the next column down. Otherwise write
   * into video memory at the offset and set the attrib byte too. */
  if (character == '\n') {
    row = get_offset_row(offset);
    offset = get_screen_offset(0, row + 1);
  } else {
    vid_mem[offset] = character;
    vid_mem[offset + 1] = attr;
    offset += 2;
  }

  /* Scrolling screen adjustment */
  offset = handle_scrolling(offset);

  /* Update the cursor position and return it */
  set_cursor_offset(offset);
  return offset;
}

static int32 get_screen_offset(const int32 col, const int32 row) {
  return 2 * (row * MAX_COLS + col);
}

static int32 get_offset_row(const int32 offset) {
  return offset / (2 * MAX_COLS);
}

static int32 get_offset_col(const int32 offset) {
  return (offset - (get_offset_row(offset) * 2 * MAX_COLS)) / 2;
}

/* Gets the cursor position using the VGA port. We ask for the high byte of the
 * cursor offset with 14 and the low byte with 15. We shift the high byte to the
 * left 8 times and add on the low byte. We then return this offset multiplied
 * by two as this is the size of a character. */
static int32 get_cursor_offset() {
  int32 offset = 0;

  port_byte_out(REG_SCREEN_CTRL, 14);
  offset = port_byte_in(REG_SCREEN_DATA) << 8;
  port_byte_out(REG_SCREEN_CTRL, 15);
  offset += port_byte_in(REG_SCREEN_DATA);

  return offset * 2;
}

/* Similar to get cursor, but we are reading out the data to the ports instead.
 * The offset and bit manipulation is reversed. */
static void set_cursor_offset(int32 offset) {
  offset /= 2;
  port_byte_out(REG_SCREEN_CTRL, 14);
  port_byte_out(REG_SCREEN_DATA, (uint8)(offset >> 8));
  port_byte_out(REG_SCREEN_CTRL, 15);
  port_byte_out(REG_SCREEN_DATA, (uint8)(offset & 0xff));
}

/* Scroll the screen down if necessary. */
static int32 handle_scrolling(int32 offset) {
  int32 i = 0;
  char *last_line = (char *)get_screen_offset(0, MAX_ROWS - 1) + VIDEO_ADDRESS;

  /* Return if the cursor is within the screen */
  if (offset < MAX_ROWS * MAX_COLS * 2) {
    return offset;
  }

  /* Shuffle back the rows */
  for (i = 1; i < MAX_ROWS; ++i) {
    mem_copy((char *)(get_screen_offset(0, i)) + VIDEO_ADDRESS,
             (char *)(get_screen_offset(0, i - 1)) + VIDEO_ADDRESS,
             MAX_COLS * 2);
  }

  /* Remove the last line */
  for (i = 0; i < MAX_COLS * 2; ++i) {
    last_line[i] = 0;
  }

  /* Move the cursor back a row and return it */
  offset -= 2 * MAX_COLS;
  return offset;
}