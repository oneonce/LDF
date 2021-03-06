/**********************************************************************************************************************
**                            Copyright(C), oneonce. 2020-2025. All rights reserved.
***********************************************************************************************************************
**文件名称: device_driver_manager.h
**功能描述: 设备驱动管理
**作       者: oneonce
**日       期: 2020.03.29
**版       本: 1.0
**其       他:
***********************************************************************************************************************/
#ifndef __DEVICE_DRIVER_MANAGER_H__
#define __DEVICE_DRIVER_MANAGER_H__
#include <interface/interface.h>
#include <platform/platform.h>

#ifdef __cplusplus
extern "C" {
#endif







/**********************************************************************************************************************
**函数名称: init_device_driver
**功能描述: 初始化设备总线，以及把平台相关驱动挂载到总线上
**输入参数: 无
**输出参数: 无
**函数返回: 无
**********************************************************************************************************************/
void init_device_driver();

/**********************************************************************************************************************
**函数名称: register_device
**功能描述: 注册设备驱动到指定的总线
**输入参数: 
**                 node: 指向device_t结构体中的bus_node成员
**                 bus_id: 指定设备所挂载的总线ID
**输出参数: 无
**函数返回: 
**                true: 挂载成功
**                false: 挂载失败
**********************************************************************************************************************/
bool register_device_driver(list_head_t* node, enum DEVICE_BUS_ID bus_id);

void release_device_driver(device_t* device);

/**********************************************************************************************************************
**函数名称: get_device_by_id
**功能描述: 根据设备ID与总线ID获取对应的设备
**输入参数:
**                 id: 设备ID
**                 bus_id: 总线ID
**输出参数: 无
**函数返回:
**                !NULL: 获取设备成功
**                NULL: 获取设备失败
**********************************************************************************************************************/
void* get_device_by_id(uint16_t id, enum DEVICE_BUS_ID bus_id);

/**********************************************************************************************************************
**函数名称: get_device_by_type
**功能描述: 根据设备类型、复用功能、以及总线ID获取对应的设备
**输入参数:
**                 type: 设备类型
**                 multiplex: 复用功能
**                 bus_id: 总线ID
**输出参数: 无
**函数返回:
**                !NULL: 获取设备成功
**                NULL: 获取设备失败
**********************************************************************************************************************/
void* get_device_by_type(enum DEVICE_TYPE type, uint32_t multiplex, enum DEVICE_BUS_ID bus_id);

/**********************************************************************************************************************
**函数名称: 锁相关操作
**功能描述: 由平台进行实现
**输入参数: 无
**输出参数: 无
**函数返回: 无
**********************************************************************************************************************/
void lock();
bool trylock();
void unlock();


#ifdef __cplusplus
}
#endif

#endif // !__DEVICE_DRIVER_MANAGER_H__
