/* =============================================================================
 *   PikOS
 * ========================================================================== */

/**
 * \file keyboard.h
 * \brief Keyboard function definitions.
 *
 * The keyboard interrupt is typically mapped to IRQ1. When an interrupt is
 * handled, we can obtain the scancode by reading I/O port 0x60 which holds the
 * data recieved from the device. This can then be sent to a function which
 * prints an ASCII representation to the screen. There are many keyboard
 * scancodes to consider. Here we only handle the general ones. Note that to
 * detect whether a key was released, we can add 0x80 to the scancode.
 *
 * \author Anthony Mercer
 *
 */

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../common/definitions.h"
#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "ports.h"

/** \typdef
 * \brief Defines the keyboard data port from which the received scancode can be
 * read.
 */
#define KEY_DATA_PORT 0x60

/**
 * \brief Registers the keyboard callback.
 * \params None.
 * \returns None.
 */
void init_keyboard(void);

#endif