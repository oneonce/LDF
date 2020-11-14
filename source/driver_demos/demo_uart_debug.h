/**********************************************************************************************************************
**                       Copyright(C), oneonce Technology Co.,Ltd. 2020-2025. All rights reserved.
***********************************************************************************************************************
**文件名称: driver_外设_xxx.h
**功能描述: 具体驱动头文件
**                注意:
**                1. 该头文件不能包含任何平台(或芯片厂商)相关的头文件
**                2. 该头文件只能被platform.c包含(include)
**作       者: oneonce
**日       期: 2020.03.27
**版       本: 1.0
**其       他:
***********************************************************************************************************************/
#ifndef __DEMO_UART_DEBUG_H__
#define __DEMO_UART_DEBUG_H__

#ifdef __cplusplus
extern "C" {
#endif




void init_demo_uart_debug();


#ifdef __cplusplus
}
#endif

#endif // !__DEMO_UART_DEBUG_H__