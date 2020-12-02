/**********************************************************************************************************************
**                            Copyright(C), oneonce. 2020-2025. All rights reserved.
***********************************************************************************************************************
*文件名称: types.h
*功能描述: 基本数据类型定义
*作       者: oneonce
*日       期: 2020.03.27
*版       本: 1.0
*其       他:
***********************************************************************************************************************/
#ifndef __TYPES_H__
#define __TYPES_H__
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif




#ifndef bool_t
	typedef unsigned char bool_t;
#endif // !bool_t

#ifndef TRUE
#define TRUE											1
#endif // !TRUE

#ifndef FALSE
#define FALSE											0
#endif // !FALSE



#ifndef int8_t
	typedef signed char int8_t;
#endif // !int8_t

#ifndef uint8_t
	typedef unsigned char uint8_t;
#endif // !uint8_t

#ifndef int16_t
	typedef short int16_t;
#endif // !int16_t

#ifndef uint16_t
	typedef unsigned short uint16_t;
#endif // !uint16_t

#ifndef int32_t
	typedef int int32_t;
#endif // !int32_t

#ifndef uint32_t
	typedef unsigned int uint32_t;
#endif // !uint32_t

#ifndef int64_t
	typedef long long int64_t;
#endif // !int64_t

#ifndef uint64_t
	typedef unsigned long long uint64_t;
#endif // !uint64_t


#ifndef COLOR

	union COLOR
	{
#ifdef LUI_BPP_16

		struct
		{
			unsigned short blue : 5;
			unsigned short green : 6;
			unsigned short red : 5;
		};
		unsigned short value;

#else

		struct
		{
			uint8_t blue;
			uint8_t green;
			uint8_t red;
			uint8_t alpha;
		};
		unsigned int value;
	};

#endif

	typedef union COLOR color_t;

#endif // ! COLOR


#ifdef __cplusplus
}
#endif

#endif // !__TYPES_H__
