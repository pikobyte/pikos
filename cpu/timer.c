/* =============================================================================
 *   PikOS
 * ========================================================================== */

/**
 * \file timer.h
 * \brief Timer function implementation.
 *
 * \author Anthony Mercer
 *
 */

#include "timer.h"

static uint32 tick = 0;

/**
 * \brief Callback function for the timer interrupt.
 *
 * The implemented callback function for timer interrupts. The only
 * functionality to handle is incrementing the tick counter.
 *
 * \param [in] reg Not used, present to conform with function pointer
 * prototype.
 * \returns None.
 */
static void timer_callback(Registers reg) {
  ++tick;
  UNUSED(reg);
}

/**
 * \desc Installs the timer_callback() function to the first handler index,
 * calculates the frequency of the timer interrupt (based on the PIT clock) and
 * communicates this to the PIT I/O port.
 */
void init_timer(const uint32 freq) {
  uint32 divisor = PIT_CLOCK / freq;
  uint8 low = lo8(divisor);
  uint8 high = hi8(divisor);

  reg_interrupt_handler(IRQ0, timer_callback);

  port_byte_out(PIT_COMM, PIT0_FLAG);
  port_byte_out(PIT0, low);
  port_byte_out(PIT0, high);
}