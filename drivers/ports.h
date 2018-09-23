/* =============================================================================
 *   PikOS
 *
 *   ports.h
 *
 *   Basic functionality for port I/O.
 *
 * ========================================================================== */

#ifndef PORTS_H
#define PORTS_H

#include "../common/definitions.h"

uint8 port_byte_in(const uint16 port);
void port_byte_out(const uint16 port, const uint8 data);
uint16 port_word_in(const uint16 port);
void port_word_out(const uint16 port, const uint16 data);

#endif