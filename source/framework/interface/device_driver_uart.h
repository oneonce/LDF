/**********************************************************************************************************************
**                            Copyright(C), oneonce. 2020-2025. All rights reserved.
***********************************************************************************************************************
*文件名称: device_driver_uart.h
*功能描述: UART驱动
*作       者: oneonce
*日       期: 2020.03.27
*版       本: 1.0
*其       他:
***********************************************************************************************************************/
#ifndef __DEVICE_DRIVER_UART_H__
#define __DEVICE_DRIVER_UART_H__
#include <core/device.h>

#ifdef __cplusplus
extern "C" {
#endif








	/* 数据位长 */
	enum UART_DATA_BITS
	{
		UART_DATA_5B = 0,
		UART_DATA_6B,
		UART_DATA_7B,
		UART_DATA_8B,
		UART_DATA_9B,

		UART_DATA_MAX // 无效(新的类型在此之前添加)
	};

	/* 停止位 */
	enum UART_STOP_BITS
	{
		UART_STOP_1B = 0,
		UART_STOP_0_5B,
		UART_STOP_2B,
		UART_STOP_1_5B,

		UART_STOP_MAX // 无效(新的类型在此之前添加)
	};

	/* 校验 */
	enum UART_PARITY
	{
		UART_PARITY_NONE = 0,
		UART_PARITY_EVEN, // 偶校验
		UART_PARITY_ODD, // 奇校验

		UART_PARITY_MAX // 无效(新的类型在此之前添加)
	};

	/* 硬件流控 */
	enum UART_HW_FLOW_CTRL
	{
		UART_HW_CTRL_NONE = 0,
		UART_HW_CTRL_RTS,
		UART_HW_CTRL_CTS,
		UART_HW_CTRL_RTS_CTS,

		UART_HW_CTRL_MAX // 无效(新的类型在此之前添加)
	};

	/* 串口参数 */
	typedef struct
	{
		uint32_t baud_rate;
		enum UART_DATA_BITS data_bits;
		enum UART_STOP_BITS stop_bits;
		enum UART_PARITY parity;
		enum UART_HW_FLOW_CTRL hw_flow_ctrl;
	} uart_cfg_parameter_t;



	/* 串口异步模式rx回调函数 */
	typedef void (*uart_rx_callback)(uint16_t device_id, uint8_t* buf, uint32_t size);

	/* 串口异步模式tx完成回调函数 */
	typedef void (*uart_tx_callback)(uint16_t device_id);



	/* 串口驱动接口 */
	typedef struct
	{
		device_t device;

		/**********************************************************************************************************************
		**函数名称: open
		**功能描述: 打开设备
		**                注:
		**                1. 若已注册rx回调函数，则为异步读模式
		**                2. 若已注册tx回调函数，则为异步写模式
		**输入参数:
		**                cfg_parameter: 串口配置参数
		**输出参数: 无
		**函数返回: 无
		**********************************************************************************************************************/
		void (*open)(uart_cfg_parameter_t* cfg_parameter);

		/**********************************************************************************************************************
		**函数名称: close
		**功能描述: 关闭设备
		**                注:
		**                1. 关闭设备时，驱动层必须把device的state修改为DEV_STATE_FREE
		**输入参数:
		**                device: 待关闭的设备
		**输出参数: 无
		**函数返回: 无
		**********************************************************************************************************************/
		void (*close)(device_t* device);

		/**********************************************************************************************************************
		**函数名称: sync_read
		**功能描述: 同步读
		**                注:
		**                1. 若已注册rx回调函数，该方法被调用时，返回异步调用错误DEV_ERR_SYNC_CALL
		**输入参数:
		**                buffer_size: 读数据缓冲区大小
		**                millisecond: 超时时间(毫秒)
		**输出参数:
		**                buffer: 读数据缓冲区
		**函数返回:
		**                >=0: 实际读取数据字节数
		**                <0:  参考ERROR_CODES
		**********************************************************************************************************************/
		int32_t (*sync_read)(uint8_t* buffer, const int32_t buffer_size, const uint32_t millisecond);

		/**********************************************************************************************************************
		**函数名称: write
		**功能描述: 写数据
		**                注:
		**                1. 若已注册tx回调函数，则为异步模式，发送完成后需调用发送完成回调函数
		**输入参数:
		**                buffer: 写数据缓冲区
		**                buffer_size: 写数据缓冲区大小
		**                millisecond: 超时时间(毫秒)
		**输出参数: 无
		**函数返回:
		**                >=0: 实际写数据字节数
		**                <0:  参考ERROR_CODES
		**********************************************************************************************************************/
		int32_t (*write)(const uint8_t* buffer, const int32_t buffer_size, const uint32_t millsecond);

		/**********************************************************************************************************************
		**函数名称: register_async_rx_callback
		**功能描述: 注册异步模式rx回调函数
		**                注:
		**                1. 必须在open之前注册
		**输入参数:
		**                callback: 回调函数
		**输出参数: 无
		**函数返回: 无
		**********************************************************************************************************************/
		void (*register_rx_callback)(uart_rx_callback callback);

		/**********************************************************************************************************************
		**函数名称: register_async_tx_callback
		**功能描述: 注册异步模式tx发送完成中断回调函数
		**                注:
		**                1. 必须在open之前注册
		**输入参数:
		**                callback: 回调函数
		**输出参数: 无
		**函数返回: 无
		**********************************************************************************************************************/
		void (*register_tx_callback)(uart_tx_callback callback);
} device_driver_uart_t;


#ifdef __cplusplus
}
#endif

#endif // !__DEVICE_DRIVER_UART_H__
