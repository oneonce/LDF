#ifndef __DRIVER_EEPROM_H__
#define __DRIVER_EEPROM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <core/device.h>



typedef struct driver_eeprom
{
	device_t device;

	/**********************************************************************************************************************
	**函数名称: open
	**功能描述: 打开设备
	**输入参数: 无
	**输出参数: 无
	**函数返回: 无
	**********************************************************************************************************************/
	void (*open)();

	/**********************************************************************************************************************
	**函数名称: close
	**功能描述: 关闭设备
	**                注:
	**                1. 关闭设备时，驱动层必须把device的state修改为DEV_STATE_FREE
	**输入参数:
	**                device: 待关闭的设备
	**输出参数: 无
	**函数返回: 指向实际数据类型的指针对象
	**********************************************************************************************************************/
	void (*close)(device_t* device);

	/**********************************************************************************************************************
	**函数名称: sync_read
	**功能描述: 同步读
	**输入参数:
	**                address: 待读取的起始地址
	**                addr_size: 待读取地址长度(字节数)
	**                buffer_size: 读数据缓冲区大小(字节数)
	**                millisecond: 超时时间(毫秒)
	**输出参数:
	**                buffer: 读数据缓冲区
	**函数返回:
	**                >=0: 实际读取数据字节数
	**                <0:  参考DEVICE_ERROR
	**********************************************************************************************************************/
	int32_t (*sync_read)(uint32_t address, uint8_t addr_size, uint8_t* buffer, const int32_t buffer_size, const uint32_t millisecond);

	/**********************************************************************************************************************
	**函数名称: write
	**功能描述: 写数据
	**输入参数:
	**                address: 待写入的起始地址
	**                addr_size: 待写入地址长度(字节数)
	**                buffer: 写数据缓冲区
	**                buffer_size: 写数据缓冲区大小
	**                millisecond: 超时时间(毫秒)
	**输出参数: 无
	**函数返回:
	**                >=0: 实际写数据字节数
	**                <0:  参考DEVICE_ERROR
	**********************************************************************************************************************/
	int32_t (*write)(uint32_t address, uint8_t addr_size, const uint8_t* buffer, const int32_t buffer_size, const uint32_t millisecond);
} driver_eeprom_t;

#ifdef __cplusplus
}
#endif

#endif // !__DRIVER_EEPROM_H__