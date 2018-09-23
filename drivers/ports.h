/* =============================================================================
 *   PikOS
 * ========================================================================== */

/**
 * \file ports.h
 * \brief Port function declarations.
 *
 * The functions used to read and write bytes and words to a given port are
 * defined here.
 *
 * \author Anthony Mercer
 *
 */

#ifndef PORTS_H
#define PORTS_H

#include "../common/definitions.h"

/**
 * \brief Reads a byte from a given port.
 * \param [in] port The port to read a byte from.
 * \returns Byte provided by the given port.
 */
uint8 port_byte_in(const uint16 port);

/**
 * \brief Writes a byte to a given port.
 * \param [in] port The port to write a byte to.
 * \param [in] data The data to be written to the port.
 * \returns None.
 */
void port_byte_out(const uint16 port, const uint8 data);

/**
 * \brief Reads a word from a given port.
 * \param [in] port The port to read a word from.
 * \returns Word provided by the given port.
 */
uint16 port_word_in(const uint16 port);

/**
 * \brief Writes a word to a given port.
 * \param [in] port The port to write a word to.
 * \param [in] data The data to be written to the port.
 * \returns None.
 */
void port_word_out(const uint16 port, const uint16 data);

#endif