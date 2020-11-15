/**********************************************************************************************************************
**                            Copyright(C), oneonce. 2020-2025. All rights reserved.
***********************************************************************************************************************
*文件名称: device_driver_spi.h
*功能描述: SPI驱动接口
*作       者: oneonce
*日       期: 2020.04.09
*版       本: 1.0
*其       他:
***********************************************************************************************************************/
#ifndef __DEVICE_DRIVER_SPI_H__
#define __DEVICE_DRIVER_SPI_H__
#include <core/device.h>

#ifdef __cplusplus
extern "C" {
#endif



/* CS控制标志 */
#define SPI_FLG_CS_START_KEEP			0x0000 // 传输之前保持最后一次CS状态(不执行任何CS操作)
#define SPI_FLG_CS_START_OPEN			0x0001 // 传输之前执行片选操作
#define SPI_FLG_CS_END_KEEP				0x0002 // 传输结束后保持片选状态
#define SPI_FLG_CS_END_CLOSE				0x0004 // 传输结束后关闭片选(不片选)




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

	/* 数据移位方向MSG/LSB */
	enum SPI_SHIFT_DIRECTION
	{
		SPI_SHIFT_DIR_MSB = 0, // MSB
		SPI_SHIFT_DIR_LSB, // LSB
	};

	/* 发送数据完成后数据线状态 */
	enum SPI_DATA_SIGNAL
	{
		SPI_DATA_SIGNAL_KEEP, // 发送完成后数据信号脚保持最后状态(高/低)
		SPI_DATA_SIGNAL_TRISTATE, // 发送完成后数据信号为三态
	};

	/* 常用SPI信号脚 */
	enum SPI_SIGNAL_PIN
	{
		SPI_SIGNAL_PIN_CS = 0,
		SPI_SIGNAL_PIN_CLK,
		SPI_SIGNAL_PIN_MOSI,
		SPI_SIGNAL_PIN_MISO,
	};

	/* SPI外设配置参数 */
	typedef struct
	{
		uint32_t speed; // 速率
		enum SPI_TYPE type; // SPI类型
		enum SPI_MODE mode; // 模式
		enum SPI_CLOCK_POLARITY polarity; // 时钟极性
		enum SPI_CLOCK_PHASE phase; // 时钟相位
		enum SPI_SHIFT_DIRECTION shift_dir; // 数据移动方向(MSB/LSB)
		enum SPI_DATA_SIGNAL data_signal; // 数据发送完成后数据信号状态
		uint16_t delay_after_cs; // 片选之后传输数据前延时时间(时间单位根据实际情况而定)
		uint16_t delay_before_cs_close; // 传输完成数据后关闭CS前的延时时间(时间单位根据实际情况而定)
	} spi_cfg_parameter_t;

	typedef struct spi_message
	{
		const void* tx_buffer; // 发送缓冲区
		void* rx_buffer; // 接收缓冲区
		int32_t rx_length; // 接收缓冲区长度
		int16_t tx_length; // 发送缓冲区长度
		uint16_t cs_flg; // 控制标志，参考SPI_FLG_CS_
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
		**                1. 关闭设备时，驱动层必须调用release_device_driver释放当前设备
		**输入参数:
		**                device: 待关闭的设备
		**输出参数: 无
		**函数返回: 无
		**********************************************************************************************************************/
		void (*close)(device_t* device);

		/**********************************************************************************************************************
		**函数名称: pin_level_ctrl
		**功能描述: 引脚电平控制
		**                注: 某些外设(如CC1101)需要手动控制信号脚以进入其他工作模式
		**输入参数:
		**                pin: 信号引脚
		**                level: 需要设置的电平
		**输出参数: 无
		**函数返回: 无
		**********************************************************************************************************************/
		void (*pin_level_ctrl)(enum SPI_SIGNAL_PIN pin, enum IO_LEVEL_EDGE level);

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
		**                <0:  参考ERROR_CODES
		**********************************************************************************************************************/
		int32_t (*transfer)(spi_message_t* msg, int32_t msg_cnt, const uint32_t millisecond);
	} device_driver_spi_t;

#ifdef __cplusplus
}
#endif

#endif // !__DEVICE_DRIVER_SPI_H__
