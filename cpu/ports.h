/* =============================================================================
 *   PikOS
 * ========================================================================== */

/**
 * \file ports.h
 * \brief Port function declarations.
 *
 * The functions used to read and write bytes and words to a given port are
 * defined here. The list of I/O port ranges are thus:
 *
 * 0x000 - 0x01F : First direct memory access (DMA) controller (floppies).
 * 0x020 - 0x021 : Master programmable interrupt controller (PIC).
 * 0x022 - 0x023 : Cyrix model processor special register access.
 * 0x040 - 0x047 : Programmable timer interval (PIT).
 * 0x060 - 0x064 : 8042 PS/2 controller.
 * 0x070 - 0x071 : CMOS and real-time clock (RTC) registers.
 * 0x080 - 0x08F : Direct memory access (DMA) page registers.
 *         0x092 : Fast A20 register.
 * 0x0A0 - 0x0A1 : Slave programmable interrupt controller (PIC).
 * 0x0C0 - 0x0DF : Second direct memory access (DMA) controller (Soundblaster).
 *         0x0E9 : Port E9 hack.
 * 0x170 - 0x177 : Secondary advanced technology (ATA) hard disk controller.
 * 0x1F0 - 0x1F7 : Primary advanced technology (ATA) hard disk controller.
 * 0x278 - 0x27A : Parallel port.
 * 0x2F8 - 0x2FF : Second serial port.
 * 0x3B0 - 0x3DF : IBM VGA and legacy video mode.
 * 0x3F0 - 0x3F7 : Floppy disk controller.
 * 0x3F8 - 0x3FF : First serial port.
 *
 * \author Anthony Mercer
 *
 */

#ifndef PORTS_H
#define PORTS_H

#include "../common/types.h"

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