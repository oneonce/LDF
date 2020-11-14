/**********************************************************************************************************************
**                            Copyright(C), oneonce. 2020-2025. All rights reserved.
***********************************************************************************************************************
*文件名称: device_driver_gpio.h
*功能描述: GPIO驱动接口
*作       者: oneonce
*日       期: 2020.04.11
*版       本: 1.0
*其       他:
***********************************************************************************************************************/
#ifndef __DEVICE_DRIVER_SPIO_H__
#define __DEVICE_DRIVER_SPIO_H__
#include <core/device.h>

#ifdef __cplusplus
extern "C" {
#endif





	typedef struct device_driver_gpio
	{
		device_t device;

		/**********************************************************************************************************************
		**函数名称: open
		**功能描述: 打开指定GPIO相关资源
		**输入参数:
		**                pin: 待打开的I/O
		**输出参数: 无
		**函数返回: 无
		**********************************************************************************************************************/
		void (*open)(uint32_t pin);

		/**********************************************************************************************************************
		**函数名称: close
		**功能描述: 关闭指定GPIO相关资源
		**输入参数: 
		**                pin: 待关闭的I/O
		**输出参数: 无
		**函数返回: 无
		**********************************************************************************************************************/
		void (*close)(uint32_t pin);

		/**********************************************************************************************************************
		**函数名称: set_direction
		**功能描述: 设置GPIO方向
		**输入参数:
		**                pin: 信号引脚
		**                direction: 方向
		**输出参数: 无
		**函数返回: 无
		**********************************************************************************************************************/
		void (*set_direction)(uint32_t pin, enum IO_DIRECTION direction);

		/**********************************************************************************************************************
		**函数名称: read
		**功能描述: 读引脚电平
		**输入参数:
		**                pin: 信号引脚
		**输出参数: 无
		**函数返回: 电平
		**********************************************************************************************************************/
		enum IO_LEVEL_EDGE (*read)(uint32_t pin);

		/**********************************************************************************************************************
		**函数名称: write
		**功能描述: 写引脚电平
		**输入参数:
		**                pin: 信号引脚
		**                level: 需要设置的电平
		**输出参数: 无
		**函数返回: 无
		**********************************************************************************************************************/
		void (*write)(uint32_t pin, enum IO_LEVEL_EDGE level);
	} device_driver_gpio_t;


#ifdef __cplusplus
}
#endif

#endif // !__DEVICE_DRIVER_SPIO_H__