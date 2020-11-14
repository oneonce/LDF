/**********************************************************************************************************************
**                            Copyright(C), oneonce. 2020-2025. All rights reserved.
***********************************************************************************************************************
**文件名称: device_state.h
**功能描述: 设备驱动状态
**作       者: oneonce
**日       期: 2020.03.29
**版       本: 1.0
**其       他:
***********************************************************************************************************************/
#ifndef __DEVICE_STATE_H__
#define __DEVICE_STATE_H__
#include <core/types.h>

#ifdef __cplusplus
extern "C" {
#endif





#define DEVICE_STATE_FREE							0 // 空闲状态
#define DEVICE_STATE_INUSE                         1 // 使用中


#ifdef __cplusplus
}
#endif

#endif // !__DEVICE_STATE_H__
