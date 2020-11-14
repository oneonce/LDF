/**********************************************************************************************************************
**                            Copyright(C), oneonce. 2020-2025. All rights reserved.
***********************************************************************************************************************
*文件名称: device_type.h
*功能描述: 设备类型
*作       者: oneonce
*日       期: 2020.03.27
*版       本: 1.0
*其       他:
***********************************************************************************************************************/
#ifndef __DEVICE_TYPE_H__
#define __DEVICE_TYPE_H__
#include <core/types.h>

#ifdef __cplusplus
extern "C" {
#endif




enum DEVICE_TYPE
{
	DEVICE_TYPE_ADC = 0,
    DEVICE_TYPE_BUZZER, // 蜂鸣器
	DEVICE_TYPE_BT, // Bluetooth
	DEVICE_TYPE_CAN,
	DEVICE_TYPE_DAC,
    DEVICE_TYPE_EEPROM, // EEPROM
	DEVICE_TYPE_EXT_INT, // 外部中断
	DEVICE_TYPE_FLASH, // 适用FLASH(内部)/NOR FLASH/NAND FLASH
    DEVICE_TYPE_FSMC, 
	DEVICE_TYPE_GPIO,
	DEVICE_TYPE_IIC,
	DEVICE_TYPE_IIS,
	DEVICE_TYPE_LED,
	DEVICE_TYPE_LCD,
    DEVICE_TYPE_MOTOR, // 电机/马达控制
	DEVICE_TYPE_MUTEX, // mutex
	DEVICE_TYPE_PWM,
    DEVICE_TYPE_SENSOR, // 传感器类
	DEVICE_TYPE_SPI,
	DEVICE_TYPE_ETH, // 网络相关，如: 有线/无线/5G
	DEVICE_TYPE_TIMER,
	DEVICE_TYPE_TOUCH,
	DEVICE_TYPE_UART,
	DEVICE_TYPE_USB,
};



#ifdef __cplusplus
}
#endif

#endif // !__DEVICE_TYPE_H__
