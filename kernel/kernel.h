/* =============================================================================
 *   PikOS
 * ========================================================================== */

/**
 * \file kernel.h
 * \brief Contains the main entry point for the PikOS kernel.
 *
 * The main function is the first call after control has been given to the
 * kernel from the boot sector. From here, the operating system runs in C with
 * some assembly functionality.
 *
 * \author Anthony Mercer
 *
 */

#ifndef KERNEL_H
#define KERNEL_H

/**
 * \brief Handles user keyboard input.
 * \param [in] input The current line buffer.
 * \returns None.
 */
void user_input(const char *input);

#endif