/* =============================================================================
 *   PikOS
 * ========================================================================== */

/**
 * \file keyboard.c
 * \brief Keyboard function implementation.
 *
 * \author Anthony Mercer
 *
 */

#include "keyboard.h"

/* Maximum number of scancodes */
#define SC_MAX 57

/* Common escape sequence scancodes */
#define BACKSPACE 0x0E
#define TAB 0x0F
#define ENTER 0x1C
#define LSHIFT 0x2A
#define LCTRL 0x1D
#define LALT 0x38
#define CAPS_LOCK 0x3A

#define MAX_BUFFER_LEN 1024
static char key_buffer[MAX_BUFFER_LEN];

const char *sc_name[] = {
    "ERROR",     "Esc",     "1", "2", "3", "4",      "5",
    "6",         "7",       "8", "9", "0", "-",      "=",
    "Backspace", "Tab",     "Q", "W", "E", "R",      "T",
    "Y",         "U",       "I", "O", "P", "[",      "]",
    "Enter",     "Lctrl",   "A", "S", "D", "F",      "G",
    "H",         "J",       "K", "L", ";", "'",      "`",
    "LShift",    "\\",      "Z", "X", "C", "V",      "B",
    "N",         "M",       ",", ".", "/", "RShift", "Keypad *",
    "LAlt",      "Spacebar"};

const char sc_str[] = {'?',  '?', '1', '2',  '3', '4',  '5', '6', '7', '8',
                       '9',  '0', '-', '=',  '?', '\t', 'Q', 'W', 'E', 'R',
                       'T',  'Y', 'U', 'I',  'O', 'P',  '[', ']', '?', '?',
                       'A',  'S', 'D', 'F',  'G', 'H',  'J', 'K', 'L', ';',
                       '\'', '`', '?', '\\', 'Z', 'X',  'C', 'V', 'B', 'N',
                       'M',  ',', '.', '/',  '?', '?',  '?', ' '};

/**
 * \brief Prints the character received from the keyboard.
 *
 * The keyboard has many scancodes, only some of which we consider here. For
 * each of these cases, this function prints either the ASCII representation of
 * the scancode or some other message. Key releases are the scancode + 0x80. We
 * do not allow the buffer to be less than 1 when backspacing as the prompt
 * symbol should remain. Similarly, the buffer has a maximum length and no input
 * can be entered longer than that length. The TAB key enters up to the number
 * of configured spaces provided there is room in the buffer.
 *
 * \params [in] scancode The number of the keyboard key that is pressed.
 * \returns None.
 */
static void keyboard_callback(Registers regs) {
  uint8 scancode = port_byte_in(KEY_DATA_PORT);

  if (scancode > SC_MAX) {
    return;
  }

  if (scancode == BACKSPACE) {
    if (strlen(key_buffer) > 0) {
      strbs(key_buffer);
      print_bs();
    }
  } else if (scancode == TAB) {
    if (strlen(key_buffer) < MAX_BUFFER_LEN - 1) {
      uint32 i = 0;
      for (i = 0; i < TAB_SIZE; ++i) {
        if (strlen(key_buffer) >= MAX_BUFFER_LEN - 1) {
          break;
        }
        strapp(key_buffer, ' ');
      }
      print_tab();
    }
  } else if (scancode == ENTER) {
    print_ln();
    user_input(key_buffer); /* kernel-controlled function */
    key_buffer[0] = '\0';
  } else {
    if (strlen(key_buffer) < MAX_BUFFER_LEN - 1) {
      char letter = sc_str[(uint8)scancode];
      char str[2];
      str[0] = letter;
      str[1] = '\0';
      strapp(key_buffer, letter);
      print(str);
    }
  }
}

/**
 * \desc Installs the keyboard callback function to the second interrupt request
 * (IRQ1).
 */
void init_keyboard(void) { reg_interrupt_handler(IRQ1, keyboard_callback); }