/**********************************************************************************************************************
**                            Copyright(C), oneonce. 2020-2025. All rights reserved.
***********************************************************************************************************************
**文件名称: platform_mutex.h
**功能描述: 平台实现的互斥锁
**                注意: 该头文件中不能包含任何平台相关头文件
**作       者: oneonce
**日       期: 2020.04.16
**版       本: 1.0
**其       他:
***********************************************************************************************************************/
#ifndef __PLATFORM_MUTEX_H__
#define __PLATFORM_MUTEX_H__
#include <interface/lock/mutex.h>

#ifdef __cplusplus
extern "C" {
#endif






void register_platform_lock();


#ifdef __cplusplus
}
#endif

#endif // !__PLATFORM_MUTEX_H__
