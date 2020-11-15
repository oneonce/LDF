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
#include <core/error_code.h>
#include <core/device_macro.h>
#include <utils/list_head.h>


#ifdef __cplusplus
extern "C" {
#endif


	/* 电平 */
	enum IO_LEVEL_EDGE
	{
		IO_LEVEL_EDGE_LOW = 0, // 低
		IO_LEVEL_EDGE_HIGH, // 高
		IO_LEVEL_EDGE_TRISTATE, // 三态
		IO_LEVEL_EDGE_RISING, // 上升沿
		IO_LEVEL_EDGE_FALLING, // 下降沿
	};

	enum IO_DIRECTION
	{
		IO_DIR_INPUT = 0, // 输入
		IO_DIR_OURPUT = 1, // 输出
	};


	/* 时间单位 */
	enum TIME_UNIT
	{
		TIME_UNIT_SEC = 0, // 秒/s
		TIME_UNIT_MS, // 毫秒/ms
		TIME_UNIT_US, // 微秒/us
		TIME_UNIT_NS, // 纳秒/ns
		TIME_UNIT_PS, // 皮秒/ps
	};


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
