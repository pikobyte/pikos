/* =============================================================================
 *   PikOS
 * ========================================================================== */

/**
 * \file definitions.h
 * \brief Typedefs and common constants.
 *
 * The fundamental integer types are redefined here for brevity. They include
 * signed and unsigned integers from 8-bits to 32-bits. This file also defines
 * common constants and macros that are used throughout the operating system.
 *
 * \author Anthony Mercer
 *
 */

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

typedef unsigned char uint8;
typedef signed char int8;
typedef unsigned short uint16;
typedef signed short int16;
typedef unsigned int uint32;
typedef signed int int32;

#define lo8(addr) (uint8)((addr)&0xFF)
#define hi8(addr) (uint8)(((addr) >> 8) & 0xFF)
#define lo16(addr) (uint16)((addr)&0xFFFF)
#define hi16(addr) (uint16)(((addr) >> 16) & 0xFFFF)

#endif