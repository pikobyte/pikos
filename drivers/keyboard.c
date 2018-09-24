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

/* Function prototypes */
void print_letter(const uint8 scancode);

/**
 * \brief Prints the character recieved from the keyboard.
 *
 * The keyboard has many scancodes, only some of which we consider here. For
 * each of these cases, this function prints either the ASCII representation of
 * the scancode or some other message. Key releases are the scancode + 0x80.
 *
 * \params [in] scancode The number of the keyboard key that is pressed.
 * \returns None.
 */
static void keyboard_callback(Registers regs) {
  uint8 scancode = port_byte_in(KEY_DATA_PORT);
  char *sc_str = {0};
  itostr(scancode, sc_str);
  print_letter(scancode);
  UNUSED(regs);
}

/**
 * \desc Installs the keyboard callback function to the second interrupt request
 * (IRQ1).
 */
void init_keyboard(void) { reg_interrupt_handler(IRQ1, keyboard_callback); }

/**
 * \brief Prints an ASCII message based on scancode.
 *
 * The keyboard has many scancodes, only some of which we consider here. For
 * each of these cases, this function prints either the ASCII representation of
 * the scancode or some other message. Key releases are the scancode + 0x80.
 *
 * \params [in] scancode The number of the keyboard key that is pressed.
 * \returns None.
 */
void print_letter(const uint8 scancode) {
  switch (scancode) {
  case 0x0:
    print("ERROR");
    break;
  case 0x1:
    print("ESC");
    break;
  case 0x2:
    print("1");
    break;
  case 0x3:
    print("2");
    break;
  case 0x4:
    print("3");
    break;
  case 0x5:
    print("4");
    break;
  case 0x6:
    print("5");
    break;
  case 0x7:
    print("6");
    break;
  case 0x8:
    print("7");
    break;
  case 0x9:
    print("8");
    break;
  case 0x0A:
    print("9");
    break;
  case 0x0B:
    print("0");
    break;
  case 0x0C:
    print("-");
    break;
  case 0x0D:
    print("+");
    break;
  case 0x0E:
    print("Backspace");
    break;
  case 0x0F:
    print("Tab");
    break;
  case 0x10:
    print("Q");
    break;
  case 0x11:
    print("W");
    break;
  case 0x12:
    print("E");
    break;
  case 0x13:
    print("R");
    break;
  case 0x14:
    print("T");
    break;
  case 0x15:
    print("Y");
    break;
  case 0x16:
    print("U");
    break;
  case 0x17:
    print("I");
    break;
  case 0x18:
    print("O");
    break;
  case 0x19:
    print("P");
    break;
  case 0x1A:
    print("[");
    break;
  case 0x1B:
    print("]");
    break;
  case 0x1C:
    print("ENTER");
    break;
  case 0x1D:
    print("LCtrl");
    break;
  case 0x1E:
    print("A");
    break;
  case 0x1F:
    print("S");
    break;
  case 0x20:
    print("D");
    break;
  case 0x21:
    print("F");
    break;
  case 0x22:
    print("G");
    break;
  case 0x23:
    print("H");
    break;
  case 0x24:
    print("J");
    break;
  case 0x25:
    print("K");
    break;
  case 0x26:
    print("L");
    break;
  case 0x27:
    print(";");
    break;
  case 0x28:
    print("'");
    break;
  case 0x29:
    print("`");
    break;
  case 0x2A:
    print("LShift");
    break;
  case 0x2B:
    print("\\");
    break;
  case 0x2C:
    print("Z");
    break;
  case 0x2D:
    print("X");
    break;
  case 0x2E:
    print("C");
    break;
  case 0x2F:
    print("V");
    break;
  case 0x30:
    print("B");
    break;
  case 0x31:
    print("N");
    break;
  case 0x32:
    print("M");
    break;
  case 0x33:
    print(",");
    break;
  case 0x34:
    print(".");
    break;
  case 0x35:
    print("/");
    break;
  case 0x36:
    print("Rshift");
    break;
  case 0x37:
    print("Keypad *");
    break;
  case 0x38:
    print("LAlt");
    break;
  case 0x39:
    print(" ");
    break;
  default:
    if (scancode <= 0x7f) {
      print("Unknown key press!");
    } else if (scancode <= 0x39 + 0x80) {
      /* Handle key release */
      print("key up ");
      print_letter(scancode - 0x80);
    } else
      print("Unknown key release!");
    break;
  }
}