/**********************************************************************************************************************
**                            Copyright(C), oneonce. 2020-2025. All rights reserved.
***********************************************************************************************************************
**文件名称: platform.h
**功能描述: 用于平台相关的外设复用功能和自定ID定义
**                注:
**                1. 本头文件提供给core层使用，用于初始化设备总线及平台设备(即把设备挂载到总线上)
**                2. 不能包含任何平台(或芯片厂商)的头文件
**                3. 只用于定义设备驱动相关的复用功能和设备自定义ID
**作       者: oneonce
**日       期: 2020.03.27
**版       本: 1.0
**其       他:
***********************************************************************************************************************/
#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#ifdef __cplusplus
extern "C" {
#endif
#include <core/device_macro.h>





/***********************************************************************************************************************
  自定义设备ID

  参考device.h中device_t中id字段
  自定义设备ID必须在[DEVICE_ID_USR_BASE, 65535]之间
***********************************************************************************************************************/
#define PLATFORM_DEV_ID_UART_DEBUG					(DEVICE_ID_USR_BASE + 0) // 自定义调试串口ID
#define PLATFORM_DEV_ID_IIC_DEMO						(DEVICE_ID_USR_BASE + `) // 自定义IIC演示ID
















/***********************************************************************************************************************
  复用功能

  1. 复用功能由硬件设计而决定
  2. 参考device.h中device_t中multiplex字段(32bit)
  3. 单个外设最多可由31种复用功能(保留0值)
***********************************************************************************************************************/

/* ADC复用功能 */
#define ADC_MUX_RESERVE								(1 << 0) // 保留，或通用(即业务层不关注复用功能)
#define ADC_MUX_VOLTAGE								(1 << 1) // 电压相关ADC(由硬件设计决定)
#define ADC_MUX_TEMPERATURE						(1 << 2) // 温度相关ADC(由硬件设计决定)
//#define ADC_MUX_...




/* Bluetooth复用功能 */
#define BT_MUX_RESERVE									(1 << 0) // 保留，或通用(即业务层不关注复用功能)




/* CAN复用功能 */
#define CAN_MUX_RESERVE								(1 << 0) // 保留，或通用(即业务层不关注复用功能)
//#define CAN_MUX_...




/* DAC复用功能 */
#define DAC_MUX_RESERVE								(1 << 0) // 保留，或通用(即业务层不关注复用功能)
//#define DAC_MUX_...




/* EEPROM复用功能 */
#define EEPROM_MUX_RESERVE						(1 << 0) // 保留，或通用(即业务层不关注复用功能)
#define EEPROM_MUX_AT24C01						(1 << 1) // AT24c01
//#define EEPROM_MUX_...




/* 外部中断复用功能 */
#define EXT_INT_MUX_RESERVE							(1 << 0) // 保留，或通用(即业务层不关注复用功能)
//#define EXT_INT_MUX_...




/* FLASH复用功能 */
#define FLASH_MUX_RESERVE							(1 << 0) // 保留，或通用(即业务层不关注复用功能)
#define FLASH_MUX_ROM									(1 << 1) // 内部/片上FLASH
#define FLASH_MUX_NOR_FLASH						(1 << 2) // NOR FLASH
#define FLASH_MUX_NAND_FLASH					(1 << 2) // NAND FLASH(JEDEC)
//#define FLASH_MUX_...




/* FSMC复用功能 */
#define FSMC_MUX_RESERVE								(1 << 0) // 保留，或通用(即业务层不关注复用功能)
#define FSMC_MUX_LCD										(1 << 1) // LCD(硬件设计决定)
#define FSMC_MUX_NOR_FLASH						(1 << 2) // NOR FLASH(硬件设计决定)
#define FSMC_MUX_NAND_FLASH						(1 << 3) // NAND FLASH(硬件设计决定)
#define FSMC_MUX_SRAM									(1 << 4) // NAND FLASH(硬件设计决定)
//#define FSMC_MUX_...



/* GPIO复用功能 */
#define GPIO_MUX_RESERVE								(1 << 0) // 保留，或通用(即业务层不关注复用功能)
#define GPIO_MUX_LED										(1 << 1) // 控制LED(硬件设计决定)
//#define GPIO_MUX_...




/* IIC复用功能 */
#define IIC_MUX_RESERVE									(1 << 0) // 保留，或通用(即业务层不关注复用功能)
#define IIC_BUS_01												(1 << 1) // 总线01
#define IIC_BUS_02												(1 << 2) // 总线01
#define IIC_BUS_03												(1 << 3) // 总线01
#define IIC_BUS_04												(1 << 4) // 总线01
#define IIC_MUX_CAMERA									(1 << 5) // 触摸使用的IIC(硬件设计决定)
#define IIC_MUX_TOUCH									(1 << 6) // 触摸使用的IIC(硬件设计决定)
//#define IIC_MUX_...




/* IIS复用功能 */
#define IIS_MUX_RESERVE									(1 << 0) // 保留，或通用(即业务层不关注复用功能)
//#define IIS_MUX_...




/* LCD复用功能 */
#define LCD_MUX_RESERVE								(1 << 0) // 保留，或通用(即业务层不关注复用功能)
//#define LCD_MUX_...




/* PWM复用功能 */
#define PWM_MUX_RESERVE								(1 << 0) // 保留，或通用(即业务层不关注复用功能)
#define PWM_MUX_MOTOR								(1 << 1) // 控制马达(硬件设计决定)
#define PWM_MUX_BUZZER								(1 << 2) // 控制蜂鸣器(硬件设计决定)
#define PWM_MUX_LED										(1 << 3) // 控制LED(硬件设计决定)
#define PWM_MUX_BG										(1 << 4) // 控制背光(硬件设计决定)
//#define PWM_MUX_...




/* SPI复用功能 */
#define SPI_MUX_RESERVE									(1 << 0) // 保留，或通用(即业务层不关注复用功能)
#define SPI_MUX_NOR_FLASH							(1 << 1) // NOR FLASH使用的SPI(硬件设计决定)
#define SPI_MUX_LCD											(1 << 2) // LCD使用的SPI(硬件设计决定)
//#define SPI_MUX_...




/* ETH复用功能 */
#define ETH_MUX_RESERVE								(1 << 0) // 保留，或通用(即业务层不关注复用功能)
#define ETH_MUX_NG											(1 << 1) // 4/5G(硬件设计决定)
#define ETH_MUX_WIFI										(1 << 2) // WIFI(硬件设计决定)
#define ETH_MUX_RJ45										(1 << 2) // 有线(硬件设计决定)
//#define ETH_MUX_...




/* TIMER复用功能 */
#define TIMER_MUX_RESERVE							(1 << 0) // 保留，或通用(即业务层不关注复用功能)
#define TIMER_MUX_MILLI_SEC							(1 << 1) // 毫秒级定时器
#define TIMER_MUX_MICRO_SEC						(1 << 2) // 微秒级定时器
#define TIMER_MUX_CAPTURE							(1 << 3) // 带捕获功能定时器




/* TOUCH复用功能 */
#define TOUCH_MUX_RESERVE							(1 << 0) // 保留，或通用(即业务层不关注复用功能)
//#define TOUCH_MUX_...




/* 串口复用功能 */
#define UART_MUX_RESERVE								(1 << 0) // 保留，或通用(即业务层不关注复用功能)
#define UART_MUX_DEBUG								(1 << 1) // 调试串口(由硬件设计决定)
#define UART_MUX_BT										(1 << 2) // 蓝牙串口(由硬件设计决定)
//#define UART_MUX_...




/* USB复用功能 */
#define USB_MUX_RESERVE								(1 << 0) // 保留，或通用(即业务层不关注复用功能)
//#define USB_MUX_...












/***********************************************************************************************************************
  平台初始化函数
***********************************************************************************************************************/
void platform_init();



#ifdef __cplusplus
}
#endif

#endif // !__PLATFORM_H__
