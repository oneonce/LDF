#include "demo_iic_eeprom_at24c01.h"
#include <core/device_driver_manager.h>





device_driver_iic_t* at24c01_iic_bus01 = NULL;

static void eeprom_at24c01_open()
{
	/* 获取EEPROM所在的IIC总线(假设为IIC_BUS_01) */
	at24c01_iic_bus01 = (device_driver_iic_t*)get_device_by_type(DEVICE_TYPE_IIC, IIC_MUX_BUS_01, DEVICE_BUS_DEFAULT); // 设备类型, 复用功能, 总线
	if (NULL != at24c01_iic_bus01)
	{
		at24c01_iic_bus01->open();
	}
}

static void eeprom_at24c01_close(device_t* device)
{
	if (NULL != at24c01_iic_bus01)
	{
		at24c01_iic_bus01->close(&at24c01_iic_bus01->device);
	}

	release_device_driver(device); // 调用驱动管理释放设备
}

static int32_t eeprom_at24c01_read(uint32_t address, uint8_t addr_size, uint8_t* buffer, const int32_t buffer_size, const uint32_t millisecond)
{
	if (NULL == at24c01_iic_bus01)
	{
		return ERROR_CODE_FAILE;
	}

	iic_message_t msgs[] = {
		{
			.addr_slave = 0xA0, // 从机地址
			.addr_bits = IIC_ADDR_BIT_7, // 7位地址
			.flag = IIC_FLG_WRITE, // 写操作
			.data_len = addr_size, // 地址大小(字节数)
			.data = (uint8_t*)&address, // 待读取的内部/寄存器地址
		},
		{ // 根据实际情况而定是否需要多个消息
			.addr_slave = 0xA0, // 从机地址
			.addr_bits = IIC_ADDR_BIT_7, // 7位地址
			.flag = IIC_FLG_READ, // 读操作
			.data_len = (uint16_t)buffer_size, // 读数据大小(字节数)
			.data = buffer, // 接受缓冲区
		},
	};

	return at24c01_iic_bus01->transfer(msgs, 2, millisecond);
}

static int32_t eeprom_at24c01_write(uint32_t address, uint8_t addr_size, const uint8_t* buffer, const int32_t buffer_size, const uint32_t millisecond)
{
	if (NULL == at24c01_iic_bus01)
	{
		return ERROR_CODE_FAILE;
	}

	iic_message_t msgs[] = {
		{
			.addr_slave = 0xA0, // 从机地址
			.addr_bits = IIC_ADDR_BIT_7, // 7位地址
			.flag = IIC_FLG_READ, // 读操作
			.data_len = addr_size, // 地址大小(字节数)
			.data = (uint8_t*)&address, // 寄存器或内部地址
		},
		{ // 根据实际情况而定是否需要多个消息
			.addr_slave = 0xA0, // 从机地址
			.addr_bits = IIC_ADDR_BIT_7, // 7位地址
			.flag = IIC_FLG_READ | IIC_FLG_NOSTART, // 读操作
			.data_len = (uint16_t)buffer_size, // 读数据大小(字节数)
			.data = (uint8_t*)buffer, // 接受缓冲区
		},
	};

	return at24c01_iic_bus01->transfer(msgs, 2, millisecond);
}


device_driver_eeprom_t eeprom_at24c01 =
{
	.device = {
		.id = 0, // 为0时由设备管理自动分配ID，>=DEVICE_ID_USR_BASE为自定义ID
		.state = DEVICE_STATE_FREE, // 空闲状态
		.use_mode = DEVICE_USE_MODE_EXCLUSIVE, // 独占模式
		.type = DEVICE_TYPE_EEPROM, // 串口类型
		.bus_id = DEVICE_BUS_DEFAULT, // 挂载默认总线上
		.multiplex = EEPROM_MUX_AT24C01, // 总线编号01
	},
	.open = eeprom_at24c01_open,
	.close = eeprom_at24c01_close,
	.read = eeprom_at24c01_read,
	.write = eeprom_at24c01_write,
};


void register_demo_iic_eeprom_at24c01()
{
	register_device_driver(&eeprom_at24c01.device.bus_node, eeprom_at24c01.device.bus_id);
}