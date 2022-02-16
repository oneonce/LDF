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
		list_head_t dev_node; // ���ڹ��ص����ߵĽڵ�
		uint16_t id; // �豸ID
		uint8_t state; // �豸״̬������driver��close()�ر�ʱ�Ѵ����device״̬��ΪDEV_STATE_FREE
		uint8_t use_mode; // ʹ��ģʽ���ο�DEVICE_USE_MODE_
		enum DEVICE_TYPE type; // �豸����
		enum DEVICE_BUS_ID bus_id; // ����ID
		uint32_t multiplex; // ���ܸ���(ÿһ�ֹ���ռ1bit)����ĳЩ�����ͨ������ñ�л���ͬ�Ĺ���
		dev_operations* ops;
/*		void* instance;
		void* (*allocate)(uint16_t id);
		void (*deallocate)(void** instance)*/;
	} dev_t;



#ifdef __cplusplus
}
#endif
