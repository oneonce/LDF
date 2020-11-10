#include "driver_iic_bus01.h"
#include <core/device_manager.h>




static void iic_demo_open()
{
}

static void iic_demo_close(device_t* device)
{
	if (NULL != device)
	{
		device->state = DEV_STATE_FREE; // 设置设备状态空闲
	}
}

static int32_t iic_demo_transfer(iic_message_t* msg, int32_t msg_cnt, const uint32_t millisecond)
{
	if ((NULL == msg) || (0 == msg_cnt))
	{
		return DEV_ERR_PARA;
	}

	for (int32_t i = 0; i < msg_cnt; i++)
	{
		// ...
	}

	return 0;
}


driver_iic_t iic_bus01 =
{
	.device = {
		//.id = PLATFORM_DEV_ID_IIC_DEMO, // 使用自定义ID，参考platform.h
		.id = 0, // 为0时由设备管理自动分配ID，>=DEVICE_ID_USR_BASE为自定义ID
		.type = DEV_TYPE_IIC, // 串口类型
		.state = DEV_STATE_FREE, // 空闲状态
		.bus_id = DEV_BUS_DEFAULT, // 挂载默认总线上
		.multiplex = IIC_BUS_01, // 总线编号01
	},
	.open = iic_demo_open,
	.close = iic_demo_close,
	.transfer = iic_demo_transfer,
};


void init_driver_iic_bus01()
{
	register_device(&iic_bus01.device.bus_node, iic_bus01.device.bus_id);
}