/**********************************************************************************************************************
**                            Copyright(C), oneonce. 2020-2025. All rights reserved.
***********************************************************************************************************************
**文件名称: device.h
**功能描述: 设备定义
**作       者: oneonce
**日       期: 2020.03.27
**版       本: 1.0
**其       他:
***********************************************************************************************************************/
#ifndef __DEVICE_H__
#define __DEVICE_H__
#include <core/device_bus.h>
#include <core/device_type.h>
#include <core/device_state.h>
#include <core/device_error.h>
#include <core/device_macro.h>
#include <utils/list_head.h>


#ifdef __cplusplus
extern "C" {
#endif




typedef struct
{
	list_head_t bus_node; // 用于挂载到总线的节点
	uint16_t id; // 设备ID
	uint8_t state; // 设备状态。调用driver的close()关闭时把传入的device状态改为DEV_STATE_FREE
    uint8_t unused; // 未使用字段
	enum DEVICE_TYPE type; // 设备类型
	enum DEVICE_BUS_ID bus_id; // 总线ID
	uint32_t multiplex; // 功能复用(每一种功能占1bit)，如某些外设可通过跳线帽切换不同的功能
} device_t;


#ifdef __cplusplus
}
#endif

#endif // !__DEVICE_H__
