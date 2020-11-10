#ifndef __DRIVER_IIC_H__
#define __DRIVER_IIC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <core/device.h>





/* IIC读写标志 */
#define IIC_FLG_WRITE							0x0000 // 写数据，主机到从机
#define IIC_FLG_READ							0x0001 // 读数据，从机到主机

#define IIC_FLG_NO_READ_ACK				0x0100 // 主机读操作不回复ACK
#define IIC_FLG_IGNORE_NAK				0x0200 // 忽略从机的ACK和NACK
#define IIC_FLG_NOSTART						0x0400 // 不发送起始信号
#define IIC_FLG_NOSTOP						0x0800 // 不发送停止信号



/* IIC地址位数 */
enum IIC_ADDR_BIT
{
	IIC_ADDR_BIT_7 = 7,
	IIC_ADDR_BIT_10 = 10,
};


/* IIC收发消息 */
typedef struct iic_message
{
	uint16_t addr_slave; // 从设备地址
	enum IIC_ADDR_BIT addr_bits; // 地址位数
	uint16_t flag; // 标志，参考IIC_FLG_
	uint16_t data_len; // 数据或从机内部寄存器/地址的长度
	uint8_t* data; // 数据或从机内部寄存器/地址
} iic_message_t;



typedef struct driver_iic
{
	device_t device;

	/**********************************************************************************************************************
	**函数名称: open
	**功能描述: 打开设备
	**输入参数: 无
	**输出参数: 无
	**函数返回: 无
	**********************************************************************************************************************/
	void (*open)();

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
	**函数名称: transfer
	**功能描述: 传输数据(收发)
	**输入参数:
	**                msg: 发送的数据
	**                msg_cnt: 数据数量
	**                millisecond: 超时时间(毫秒)
	**输出参数: 
	**                msg: 收到的数据
	**函数返回:
	**                >=0: 实际读取数据字节数
	**                <0:  参考DEVICE_ERROR
	**********************************************************************************************************************/
	int32_t (*transfer)(iic_message_t* msg, int32_t msg_cnt, const uint32_t millisecond);
} driver_iic_t;

#ifdef __cplusplus
}
#endif

#endif // !__DRIVER_IIC_H__
