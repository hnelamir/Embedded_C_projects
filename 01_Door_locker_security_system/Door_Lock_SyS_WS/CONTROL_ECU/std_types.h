/*
 *	std_types.h
 *
 *	types for AVR
 *      Author: Alhussien Nasrallah
 */

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

typedef unsigned char boolen;

#ifndef TRUE
#define TRUE (0u)
#endif
#ifndef FALSE
#define FALSE (1u)
#endif

#define LOGIC_LOW (0u)
#define LOGIC_HIGH (1u)

#define NULL_Ptr ((void*)0)

typedef unsigned char       uint8;
typedef signed char         sint8;
typedef unsigned short      uint16;
typedef signed short        sint16;
typedef unsigned long       uint32;
typedef signed long         sint32;
typedef unsigned long long  uint64;
typedef signed long long    sint64;
typedef double              float32;
typedef float               float64;


#endif /* STD_TYPES_H_ */
