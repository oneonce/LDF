/**********************************************************************************************************************
**                            Copyright(C), oneonce. 2020-2025. All rights reserved.
***********************************************************************************************************************
**文件名称: device_code.h
**功能描述: 设备驱动错误定义
**作       者: oneonce
**日       期: 2020.03.29
**版       本: 1.0
**其       他:
***********************************************************************************************************************/
#ifndef __ERROR_CODES_H__
#define __ERROR_CODES_H__

#ifdef __cplusplus
extern "C" {
#endif






enum ERROR_CODES
{
	ERROR_CODE_SUCCESS = 0,
	ERROR_CODE_FAILE = -1, // 未定义的错误
	ERROR_CODE_PARAMETER = -2, // 参数错误
	ERROR_CODE_NO_MORE_MEM = -3, // 内存不足
	ERROR_CODE_SYNC_CALL = -4, // 异步模式调用同步方法错误
};


#ifdef __cplusplus
}
#endif

#endif // !__ERROR_CODES_H__