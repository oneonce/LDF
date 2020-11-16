/**********************************************************************************************************************
**                            Copyright(C), oneonce. 2020-2025. All rights reserved.
***********************************************************************************************************************
**文件名称: platform.c
**功能描述: 用于平台相关的初始化
**                注:
**                1. 所有外设驱动头文件都包含在当前文件中
**                2. 在platform_init()中调用所有需要挂载到总线外设驱动的初始化函数
**作       者: oneonce
**日       期: 2020.03.28
**版       本: 1.0
**其       他:
***********************************************************************************************************************/
#include <platform/platform.h>
#include <platform/platform_mutex.h>

/* UART */
#include <demo_uart_debug.h>

/* IIC */
#include <demo_iic_bus01.h>
#include <demo_iic_eeprom_at24c01.h>

/* SPI */
#include <demo_spi_bus01.h>

//#include ...









/**********************************************************************************************************************
**函数名称: platform_init
**功能描述: 平台初始化，所有设备驱动都必须在该文件中调用驱动初始化
**输入参数: 无
**输出参数: 无
**函数返回: 无
**********************************************************************************************************************/
void platform_init()
{
	register_platform_lock(); // platform mutex

	/* UART */
	register_demo_uart_debug();

	/* IIC */
	register_demo_iic_bus01();

	register_demo_iic_eeprom_at24c01();

	/* SPI */
	register_demo_spi_bus01();
}


