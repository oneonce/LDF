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
	DEV_TYPE_ADC = 0,
    DEV_TYPE_BUZZER, // 蜂鸣器
	DEV_TYPE_BT, // Bluetooth
	DEV_TYPE_CAN,
	DEV_TYPE_DAC,
    DEV_TYPE_EEPROM, // EEPROM
	DEV_TYPE_EXT_INT, // 外部中断
	DEV_TYPE_FLASH, // 适用FLASH(内部)/NOR FLASH/NAND FLASH
    DEV_TYPE_FSMC, 
	DEV_TYPE_GPIO,
	DEV_TYPE_IIC,
	DEV_TYPE_IIS,
	DEV_TYPE_LED,
	DEV_TYPE_LCD,
    DEV_TYPE_MOTOR, // 电机/马达控制
	DEV_TYPE_PWM,
    DEV_TYPE_SENSOR, // 传感器类
	DEV_TYPE_SPI,
	DEV_TYPE_ETH, // 网络相关，如: 有线/无线/5G
	DEV_TYPE_TIMER,
	DEV_TYPE_TOUCH,
	DEV_TYPE_UART,
	DEV_TYPE_USB,
};



#ifdef __cplusplus
}
#endif

#endif // !__DEVICE_TYPE_H__
