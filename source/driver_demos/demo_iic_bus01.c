#include "demo_iic_bus01.h"
#include <core/device_driver_manager.h>




static void iic_bus01_open()
{
}

static void iic_bus01_close(device_t* device)
{
	release_device_driver(device); // 调用驱动管理释放设备
}

static int32_t iic_bus01_transfer(iic_message_t* msg, int32_t msg_cnt, const uint32_t millisecond)
{
	if ((NULL == msg) || (0 == msg_cnt))
	{
		return ERROR_CODE_PARAMETER;
	}

	for (int32_t i = 0; i < msg_cnt; i++)
	{
		// ...
	}

	return 0;
}


device_driver_iic_t iic_bus01 =
{
	.device = {
		//.id = DEVICE_ID_IIC_BUS01, // 使用自定义ID，参考platform.h
		.id = 0, // 为0时由设备管理自动分配ID，>=DEVICE_ID_USR_BASE为自定义ID
		.type = DEVICE_TYPE_IIC, // IIC总线类型
		.state = DEVICE_STATE_FREE, // 空闲状态
		.bus_id = DEVICE_BUS_DEFAULT, // 挂载默认总线上
		.multiplex = IIC_MUX_BUS_01, // IIC总线编号01
	},
	.open = iic_bus01_open,
	.close = iic_bus01_close,
	.transfer = iic_bus01_transfer,
};


void init_demo_iic_bus01()
{
	register_device_driver(&iic_bus01.device.bus_node, iic_bus01.device.bus_id);
}
