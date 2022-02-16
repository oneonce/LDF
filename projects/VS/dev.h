#pragma once
#include <core/device_bus.h>
#include <core/device_type.h>
#include <core/device_state.h>
#include <core/error_codes.h>
#include <core/device_macro.h>
#include <utils/list_head.h>



#ifdef __cplusplus
extern "C" {
#endif


	typedef struct
	{
		void (*open)(void* parameter);
		void (*close)();
		uint32_t(*read)(uint8_t* buf, const uint32_t size, const uint32_t millisecond);
		uint32_t(*write)(const const uint8_t* buf, const uint32_t size, const uint32_t millsecond);
		uint32_t(*ioctl)(uint32_t cmd, const void* in_buf, const uint32_t in_size, void* out_buf, const uint32_t millsecond);
	} dev_operations;


	typedef struct
	{
		list_head_t dev_node; // 用于挂载到总线的节点
		uint16_t id; // 设备ID
		uint8_t state; // 设备状态。调用driver的close()关闭时把传入的device状态改为DEV_STATE_FREE
		uint8_t use_mode; // 使用模式，参考DEVICE_USE_MODE_
		enum DEVICE_TYPE type; // 设备类型
		enum DEVICE_BUS_ID bus_id; // 总线ID
		uint32_t multiplex; // 功能复用(每一种功能占1bit)，如某些外设可通过跳线帽切换不同的功能
		dev_operations* ops;
/*		void* instance;
		void* (*allocate)(uint16_t id);
		void (*deallocate)(void** instance)*/;
	} dev_t;



#ifdef __cplusplus
}
#endif
