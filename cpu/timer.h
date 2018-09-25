/* =============================================================================
 *   PikOS
 * ========================================================================== */

/**
 * \file timer.h
 * \brief Timer function definitions.
 *
 * The programmable interval timer (PIT) has the I/O port range 0x40 to 0x47.
 * The bytes are used for the following:
 *
 * 0x40 : Channel 0 data port.
 * 0x41 : Channel 1 data port.
 * 0x42 : Channel 2 data port.
 * 0x43 : Command register (read is ignored). The bits are:
 *  6 and 7 : channel select
 *    0 0 - channel 0
 *    0 1 - channel 1
 *    1 0 - channel 2
 *    1 1 - Read back (Intel 8254 only)
 *  4 and 5 : access mode
 *    0 0 - latch count value command
 *    0 1 - lobyte only
 *    1 0 - hibyte only
 *    1 1 - lobyte and hibyte
 *  1 to 3 : operating mode
 *    0 0 0 - mode 0, interrupt on terminal count
 *    0 0 1 - mode 1, hardware re-triggerable one-shot
 *    0 1 0 - mode 2, rate generator
 *    0 1 1 - mode 3, square-wave generator
 *    1 0 0 - mode 4, software triggered strobe
 *    1 1 0 - mode 2, same as 010
 *    1 1 1 - mode 3, same as 011
 *  0 : BCD/Binary mode
 *    0 - 16-bit binary
 *    1 - four-digit BCD
 *
 * The channel 0 of the PIT connects up to IRQ0.
 *
 * \author Anthony Mercer
 *
 */

#ifndef TIMER_H
#define TIMER_H

#include "../common/types.h"
#include "../common/string.h"
#include "../drivers/screen.h"
#include "isr.h"

/** \typdef
 * \brief The internal clock frequency of the programmable interval timer.
 */
#define PIT_CLOCK 1193180

/** \typdef
 * \brief The PIT channel 0 port.
 */
#define PIT0 0x40

/** \typdef
 * \brief The PIT command port.
 */
#define PIT_COMM 0x43

/** \typdef
 * \brief Channel 0 flag: access mode lo/hi, mode 3 square wave generator,
 * 16-bit binary.
 */
#define PIT0_FLAG 0x36

/**
 * \brief Registers the timer callback and sends data to PIT I/O port.
 * \param [in] freq The frequency in Hertz to update the timer interrupt.
 * \returns None.
 */
void init_timer(const uint32 freq);

#endif