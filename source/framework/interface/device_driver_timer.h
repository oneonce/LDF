/**********************************************************************************************************************
**                            Copyright(C), oneonce. 2020-2025. All rights reserved.
***********************************************************************************************************************
*文件名称: device_driver_timer.h
*功能描述: 定时器驱动接口
*作       者: oneonce
*日       期: 2020.04.21
*版       本: 1.0
*其       他:
***********************************************************************************************************************/
#ifndef __DEVICE_DRIVER_TIMER_H__
#define __DEVICE_DRIVER_TIMER_H__
#include <core/device.h>

#ifdef __cplusplus
extern "C" {
#endif



	/* 定时器类型 */
	enum TIMER_TYPE
	{
		TIMER_TYPE_NORMAL =0, // 普通定时器
		TIMER_TYPE_CAPTURE, // 捕获
		TIMER_TYPE_COMPARE, // 输出比较
		TIMER_TYPE_PWM, // PWM
	};

	/* 定时器模式 */
	enum TIMER_MODE
	{
		TIMER_MODE_REPEAT = 0, // 重复定时
		TIMER_MODE_SINGLE_SHOT, // 单次定时
	};

	/* 捕获信息 */
	typedef struct
	{
		enum TIME_UNIT time_unit; // 时间单位，参考TIME_UNIT
		uint32_t high_time; // 高电平时间
		uint32_t low_time; // 低电平时间
	} timer_capture_info_t;



	/**********************************************************************************************************************
	**函数名称: timer_event_callback
	**功能描述: 定时器时间回调函数
	**                注:
	**                1. 普通定时器忽略capture_msg(即为NULL)
	**                2. 作为捕获时，capture_msg表示捕获信息
	**输入参数:
	**                device_id: 定时器id
	**                channel: 通道
	**                capture_msg: 捕获信息
	**输出参数: 无
	**函数返回: 无
	**********************************************************************************************************************/
	typedef void (*timer_event_callback)(uint16_t device_id, int8_t channel, timer_capture_info_t* capture_info);





	typedef struct device_driver_timer
	{
		device_t device;

		/**********************************************************************************************************************
		**函数名称: open
		**功能描述: 打开
		**输入参数:
		**                mode: 定时器模式，参考TIMER_MODE
		**输出参数: 无
		**函数返回: 无
		**********************************************************************************************************************/
		void (*open)(enum TIMER_MODE mode);

		/**********************************************************************************************************************
		**函数名称: close
		**功能描述: 关闭
		**                注:
		**                1. 关闭设备时，驱动层必须调用release_device_driver释放当前设备
		**                2. 若存在多通道，则关闭时需检查所有通道状态
		**输入参数:
		**                device: 待关闭的设备
		**输出参数: 无
		**函数返回: 无
		**********************************************************************************************************************/
		void (*close)(device_t* device);

		/**********************************************************************************************************************
		**函数名称: get_free_channel
		**功能描述: 获取普通定时器空闲通道。启动通道之前获取通道
		**                注:
		**                1. 对于PWM、捕获、输出比较等通道在platform.h中定义，参考TIMER_PWM_CH_, TIMER_CAPTURE_CH_, TIMER_COMPARE_CH_
		**输入参数: 无
		**输出参数: 无
		**函数返回: 
		**                 >=0: 具体的通道
		**                 <0: 参考ERROR_CODES
		**                       典型错误:
		**                       不支持: ERROR_CODE_NOT_SUPPORT
		**                       已用完: ERROR_CODE_NO_MORE
		**********************************************************************************************************************/
		int8_t (*get_free_channel)();

		/**********************************************************************************************************************
		**函数名称: start
		**功能描述: 启动定时
		**                注意:
		**                1. 作为普通定时和捕获时，period_time代表定时时间，忽略pulse_width参数
		**                2. 作为PWM时，period代表周期，pulse_width代表占空比
		**输入参数:
		**                channel: 通道(若无通道，则忽略)
		**                period_time: 定时时间/周期
		**                pulse_width: 占空比
		**输出参数: 无
		**函数返回: 无
		**********************************************************************************************************************/
		void (*start)(int8_t channel, uint32_t period_time, uint32_t pulse_width);

		/**********************************************************************************************************************
		**函数名称: stop
		**功能描述: 停止定时
		**输入参数:
		**                channel: 通道(若无通道，则忽略)
		**输出参数: 无
		**函数返回: 无
		**********************************************************************************************************************/
		void (*stop)(int8_t channel);

		/**********************************************************************************************************************
		**函数名称: register_event_callback
		**功能描述: 注册指定通道时间回调函数
		**					注: 到时/超时回调函数需在open之前打开
		**输入参数:
		**                channel: 通道(若无通道，则忽略)
		**                callback: 回调函数
		**输出参数: 无
		**函数返回: 无
		**********************************************************************************************************************/
		void (*register_event_callback)(int8_t channel, timer_event_callback callback);

	} device_driver_timer_t;


#ifdef __cplusplus
}
#endif

#endif // !__DEVICE_DRIVER_TIMER_H__
