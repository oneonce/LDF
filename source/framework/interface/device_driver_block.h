/**********************************************************************************************************************
**                            Copyright(C), oneonce. 2020-2025. All rights reserved.
***********************************************************************************************************************
*文件名称: device_driver_blk.h
*功能描述: 块设备驱动接口
*作       者: oneonce
*日       期: 2020.04.23
*版       本: 1.0
*其       他:
***********************************************************************************************************************/
#ifndef __DEVICE_DRIVER_BLOCK_H__
#define __DEVICE_DRIVER_BLOCK_H__

#include <core/device.h>

#ifdef __cplusplus
extern "C" {
#endif



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
		**函数名称: read_id
		**功能描述: 读设备ID
		**输入参数: 无
		**输出参数: 无
		**函数返回: 
		**                >=0:具体ID
		**                <0: 失败，参考ERROR_CODES
		**********************************************************************************************************************/
		int32_t (*read_id)();

		/**********************************************************************************************************************
		**函数名称: get_block_cnt
		**功能描述: 获取块总数
		**输入参数: 无
		**输出参数: 无
		**函数返回:
		**                >=0: 块总数
		**                <0: 失败，参考ERROR_CODES
		**********************************************************************************************************************/
		int32_t (*get_block_cnt)();

		/**********************************************************************************************************************
		**函数名称: get_page_cnt_per_block
		**功能描述: 获取每一块有多少页
		**输入参数: 无
		**输出参数: 无
		**函数返回:
		**                >=0: 页数
		**                <0: 失败，参考ERROR_CODES
		**********************************************************************************************************************/
		int32_t (*get_page_cnt_per_block)();

		/**********************************************************************************************************************
		**函数名称: get_start_free_block_addr
		**功能描述: 获取首个可用的块地址
		**输入参数: 无
		**输出参数: 无
		**函数返回:
		**                >=0: 首个可用的块地址
		**                <0: 失败，参考ERROR_CODES
		**********************************************************************************************************************/
		uint32_t (*get_start_free_block_addr)();

		/**********************************************************************************************************************
		**函数名称: get_free_block_cnt
		**功能描述: 获取可用块个数
		**输入参数: 无
		**输出参数: 无
		**函数返回:
		**                >=0: 可用块个数
		**                <0: 失败，参考ERROR_CODES
		**********************************************************************************************************************/
		uint32_t (*get_free_block_cnt)();

		/**********************************************************************************************************************
		**函数名称: get_page_size
		**功能描述: 获取页大小
		**输入参数: 无
		**输出参数: 无
		**函数返回:
		**                >=0: 页大小
		**                <0: 失败，参考ERROR_CODES
		**********************************************************************************************************************/
		int32_t (*get_page_size)();

		/**********************************************************************************************************************
		**函数名称: read_page
		**功能描述: 读页数据
		**输入参数:
		**                address: 页地址
		**                size: 读数据大小
		**                millisecond: 超时时间(毫秒)
		**输出参数: 
		**                buf: 数据缓冲区
		**函数返回:
		**                >=0: 成功
		**                <0: 失败，参考ERROR_CODES
		**********************************************************************************************************************/
		int32_t (*read_page) (uint32_t address, uint8_t* buf, int32_t size, const uint32_t millsecond);

		/**********************************************************************************************************************
		**函数名称: write_page
		**功能描述: 写页数据
		**输入参数:
		**                address: 页地址
		**                buf: 数据缓冲区
		**                size: 写数据大小
		**                millisecond: 超时时间(毫秒)
		**输出参数: 无
		**函数返回:
		**                >=0:成功
		**                <0: 失败，参考ERROR_CODES
		**********************************************************************************************************************/
		int32_t (*write_page)(uint32_t address, const uint8_t* buf, int32_t size, const uint32_t millsecond);

		/**********************************************************************************************************************
		**函数名称: erase_block
		**功能描述: 擦除块
		**输入参数:
		**                address: 块地址
		**                millisecond: 超时时间(毫秒)
		**输出参数: 无
		**函数返回:
		**                >=0: 擦除成功
		**                <0: 擦除失败，参考ERROR_CODES
		**********************************************************************************************************************/
		int32_t (*erase_block)(uint32_t address, const uint32_t millsecond);
	} device_driver_block_t;

#ifdef __cplusplus
}
#endif

#endif // !__DEVICE_DRIVER_BLOCK_H__
