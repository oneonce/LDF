/**********************************************************************************************************************
**                            Copyright(C), oneonce. 2020-2025. All rights reserved.
***********************************************************************************************************************
**文件名称: device_macro.h
**功能描述: 设备驱动宏定义
**作       者: oneonce
**日       期: 2020.03.29
**版       本: 1.0
**其       他:
***********************************************************************************************************************/
#ifndef __DEVICE_MACRO_H__
#define __DEVICE_MACRO_H__

#ifdef __cplusplus
extern "C" {
#endif



/* 用户自定义设备ID基值 */
#define DEVICE_ID_USR_BASE						1024 // 用户自定义设备ID最小值





/* 设备使用模式 */
/*
1. 独占模式
1.1. 外设只能被单个使用者使用时
1.2 前一个使用者关闭后其他使用者才能使用
*/
#define DEVICE_USE_MODE_EXCLUSIVE		0

/*
2. 共享模式
2.1. 外设可以同时被多个使用者使用时;
2.2. 关闭设备驱动时需检查所有使用者使用情况
*/
#define DEVICE_USE_MODE_SHARED			1




/* 资源数量 */
#define DEVICE_RES_INFINITE_TOTAL			0xFFFFFFFF // 总资源无限大
#define DEVICE_RES_INFINITE_FREE			0xFFFFFFFE // 空闲/可用源无限大


#ifdef __cplusplus
}
#endif

#endif // !__DEVICE_MACRO_H__
