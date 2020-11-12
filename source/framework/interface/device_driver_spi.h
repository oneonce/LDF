/**********************************************************************************************************************
**                            Copyright(C), oneonce. 2020-2025. All rights reserved.
***********************************************************************************************************************
*文件名称: device_driver_spi.h
*功能描述: 串口驱动
*作       者: oneonce
*日       期: 2020.04.09
*版       本: 1.0
*其       他:
***********************************************************************************************************************/
#ifndef __DEVICE_DRIVER_SPI_H__
#define __DEVICE_DRIVER_SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <core/device.h>



	enum SPI_TYPE
	{
		SPI_TYPE_SPI = 0, // normal-SPI
		SPI_TYPE_DSPI, // dual-SPI
		SPI_TYPE_QSPI, // quad-SPI
	};

	enum SPI_MODE
	{
		SPI_MODE_MASTER = 0, // 主
		SPI_MODE_SLAVE, // 从
	};

	/* 时钟极性 */
	enum SPI_CLOCK_POLARITY
	{
		SPI_CPOL_LOW = 0, // 空闲的时候SCLK电平是低电平
		SPI_CPOL_HEIGH, // 空闲的时候SCLK电平是高电平
	};

	/* 时钟相位 */
	enum SPI_CLOCK_PHASE
	{
		SPI_CPHA_FIRST = 0, // 第一个时钟边缘采集数据
		SPI_CPHA_SECOND, // 第二个时钟边缘采集数据
	};

	enum SPI_FIRST_TRANSFER
	{
		SPI_FIRST_MSB = 0, // MSB
		SPI_FIRST_LSB, // LSB
	};

	enum SPI_SIGNAL_PIN
	{
		SPI_SIGNAL_PIN_CS = 0,
		SPI_SIGNAL_PIN_CLK,
		SPI_SIGNAL_PIN_MOSI,
		SPI_SIGNAL_PIN_MISO,
	};

	enum SPI_PIN_LEVEL
	{
		SPI_PIN_LEVEL_LOW = 0,
		SPI_PIN_LEVEL_HIGH,
	};

	typedef struct spi_cfg_parameter
	{
		uint32_t speed; // 速率
		enum SPI_TYPE type; // SPI类型
		enum SPI_MODE mode; // 模式
		enum SPI_CLOCK_POLARITY polarity; // 时钟极性
		enum SPI_CLOCK_PHASE phase; // 时钟相位
		enum SPI_FIRST_TRANSFER first_trans; // 第一个发送数据的有效位
	} spi_cfg_parameter_t;

	typedef struct spi_message
	{
		const void* tx_buffer; // 发送缓冲区
		void* rx_buffer; // 接收缓冲区
		uint32_t tx_length; // 发送缓冲区长度
		uint32_t rx_length; // 接收缓冲区长度
		uint8_t data_bits; // 数据位宽，如: 8/16/32bit
		uint8_t change_cs; // 传输后成后是否翻转CS，为0不改变CS信号，为1时表明传输完成后改变CS信号(即不片选)
		uint16_t cs_cmd; // 片选命令，实际值自定义
		uint16_t delay_after_cs; // 片选之后传输数据前延时时间(时间单位根据实际情况而定)
		uint16_t delay_before_cs_change; // 传输完成数据后改变CS前的延时时间(时间单位根据实际情况而定)
	} spi_message_t;


	typedef struct device_driver_spi
	{
		device_t device;

		/**********************************************************************************************************************
		**函数名称: open
		**功能描述: 打开设备
		**输入参数: 
		**                cfg_parameter: SPI配置参数
		**输出参数: 无
		**函数返回: 无
		**********************************************************************************************************************/
		void (*open)(spi_cfg_parameter_t* cfg_parameter);

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
		**函数名称: pin_level_control
		**功能描述: 引脚电平控制
		**                注: 某些外设(如CC1101)需要手动控制信号脚以进入其他工作模式
		**输入参数:
		**                pin: 信号引脚
		**                level: 需要设置的电平
		**输出参数: 无
		**函数返回: 指向实际数据类型的指针对象
		**********************************************************************************************************************/
		void (*pin_level_control)(enum SPI_SIGNAL_PIN pin, enum SPI_PIN_LEVEL level);

		/**********************************************************************************************************************
		**函数名称: transfer
		**功能描述: 传输数据(收发)
		**输入参数:
		**                msg: 发送的数据
		**                msg_cnt: 数据数量
		**                millisecond: 超时时间(毫秒)
		**输出参数:
		**                msg: 收到的数据
		**函数返回:
		**                >=0: 实际传输数据字节数
		**                <0:  参考DEVICE_ERROR
		**********************************************************************************************************************/
		int32_t (*transfer)(spi_message_t* msg, int32_t msg_cnt, const uint32_t millisecond);
	} device_driver_spi_t;

#ifdef __cplusplus
}
#endif

#endif // !__DEVICE_DRIVER_SPI_H__
