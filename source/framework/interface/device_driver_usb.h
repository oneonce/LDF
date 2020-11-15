/**********************************************************************************************************************
**                            Copyright(C), oneonce. 2020-2025. All rights reserved.
***********************************************************************************************************************
*文件名称: device_driver_usb.h
*功能描述: USB驱动接口
*作       者: oneonce
*日       期: 2020.04.26
*版       本: 1.0
*其       他:
***********************************************************************************************************************/
#ifndef __DEVICE_DRIVER_USB_H__
#define __DEVICE_DRIVER_USB_H__
#include <core/device.h>

#ifdef __cplusplus
extern "C" {
#endif


/* 端点类型 */
#define USB_EP_TYPE_CONTROL					0 // 控制端点
#define USB_EP_TYPE_ISOC							1 // 同步端点
#define USB_EP_TYPE_BULK							2 // 批量端点
#define USB_EP_TYPE_INT								3 // 中断端点


/* 端点方向 */
#define USB_EP_DIR_OUT								0
#define USB_EP_DIR_IN									0x80 // MASK


/* 请求&类型 */
/* 接收者 */
#define USB_REQ_REC_DEVICE						0 // 设备
#define USB_REQ_REC_INTF							1 // 接口
#define USB_REQ_REC_EP								2 // 端点

/* 类型 */
#define USB_REQ_TYPE_STD							0 // 标准
#define USB_REQ_TYPE_CLASS						1 // 类
#define USB_REQ_TYPE_VENDOR					2 // 厂商自定义

/* 方向 */
#define USB_REQ_DIR_HOST_2_DEV				0 // 主机到从机
#define USB_REQ_DIR_DEV_2_HOST				1 // 从机到主机

/* 请求号 */
#define USB_REQ_NO_GET_STATUS				0
#define USB_REQ_NO_CLEAR_FEATURE			1
//#define USB_REQ_NO_
#define USB_REQ_NO_SET_FEATURE				3
//#define USB_REQ_NO_
#define USB_REQ_NO_SET_ADDRESS				5
#define USB_REQ_NO_GET_DESCRIPTION		6
#define USB_REQ_NO_SET_DESCRIPTION		7
#define USB_REQ_NO_GET_CONFIGRATION	8
#define USB_REQ_NO_SET_CONFIGRATION	9
#define USB_REQ_NO_GET_INTERFACE			10
#define USB_REQ_NO_SET_INTERFACE			11
#define USB_REQ_NO_SYNCH_FRAME			12




	typedef struct usb_endpoint
	{
		uint8_t address; // 端点地址，输入端点: 最高位&USB_EP_DIR_IN > 0
        uint8_t direction; // 方向，参考USB_EP_DIR_
		uint8_t type; // 端点类型，参考USB_EP_TYPE_
		uint8_t interval; // 时间间隔
		uint16_t max_packet_size; // 端点所支持的最大包长度
	} usb_endpoint_t;

	typedef struct
	{
		uint8_t desc_type; // 描述符类型，接口描述符类为0x04
		uint8_t number; // 接口号
		uint8_t endpoint_cnt; // 端点数
		uint8_t interface_class; // 接口所使用的类，如HID类为0x03
		usb_endpoint_t* endpoints; // 接口下的端点
	} usb_interface_t;

	typedef struct
	{
		uint8_t recipient : 5; // 接收者，参考USB_REQ_REC_
		uint8_t type : 2; // 类型，参考USB_REQ_TYPE_
		uint8_t direction : 1; // 方向，参考USB_REQ_DIR_
	} usb_request_type_t;



	typedef struct
	{
		device_t device;

		/**********************************************************************************************************************
		**函数名称: open
		**功能描述: 打开
		**输入参数: 无
		**输出参数: 无
		**函数返回: 无
		**********************************************************************************************************************/
		void (*open)();

		/**********************************************************************************************************************
		**函数名称: close
		**功能描述: 关闭
		**                注:
		**                1. 关闭设备时，驱动层必须调用release_device_driver释放当前设备
		**输入参数:
		**                device: 待关闭的设备
		**输出参数: 无
		**函数返回: 无
		**********************************************************************************************************************/
		void (*close)(device_t* device);

		/**********************************************************************************************************************
		**函数名称: get_interface
		**功能描述: 获取接口
		**输入参数: 无
		**输出参数: 
		**                interfaces: 指向USB接口指针
		**函数返回: 
		**                >0: 获取接口成功
		**                =0: 无接口?发生错误
		**                <0:  参考ERROR_CODES
		**********************************************************************************************************************/
		int32_t (*get_interface)(usb_interface_t* interfaces);

		/**********************************************************************************************************************
		**函数名称: connect
		**功能描述: 连接接口，即使用该接口
		**输入参数: 
		**                intf: 被连接的接口
		**输出参数: 无
		**函数返回:
		**                >=0: 连接成功
		**                <0:  参考ERROR_CODES
		**********************************************************************************************************************/
		int32_t (*connect)(usb_interface_t* intf);

		/**********************************************************************************************************************
		**函数名称: disconnect
		**功能描述: 断开接口连接
		**输入参数:
		**                intf: 被断开的接口
		**输出参数: 无
		**函数返回:
		**                >=0: 断开连接成功
		**                <0:  参考ERROR_CODES
		**********************************************************************************************************************/
		int32_t (*disconnect)(usb_interface_t* intf);

		/**********************************************************************************************************************
		**函数名称: control_transfer
		**功能描述: 控制传输
		**输入参数:
		**                request_type: 请求类型，参考USB_REQ_TYPE_
		**                req_no: 请求号，参考USB_REQ_NO_
		**                value: 根据不同的请求不同，参考USB或自定义协议
		**                index: 根据不同的请求不同，参考USB或自定义协议
		**                buffer: 读/写缓冲区
		**                size: 读/写大小(字节数)
		**                millisecond: 超时时间(毫秒)
		**输出参数: 无
		**函数返回:
		**                >=0: 实际传输字节数
		**                <0:  参考ERROR_CODES
		**********************************************************************************************************************/
		int32_t (*control_transfer)(usb_request_type_t req_type, int32_t req_no, int32_t value, int32_t index, uint8_t * buffer, int32_t size, uint32_t millsecond);

		/**********************************************************************************************************************
		**函数名称: bulk_transfer
		**功能描述: 批量传输
		**输入参数:
		**                endpoint: 端点
		**                data: 写数据或读缓冲区
		**                size: 写数据大小或读缓冲区大小
		**                millsecond: 传输超时时间
		**输出参数: 无
		**函数返回: 
		**                >=0: 实际传输字节数
		**                <0:  参考ERROR_CODES
		**********************************************************************************************************************/
		int32_t (*bulk_transfer)(usb_endpoint_t* endpoint, uint8_t* data, int32_t size, uint32_t millsecond);
	} device_driver_usb_t;


#ifdef __cplusplus
}
#endif

#endif // !__DEVICE_DRIVER_USB_H__
