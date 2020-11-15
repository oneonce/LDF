/**********************************************************************************************************************
**                            Copyright(C), oneonce. 2020-2025. All rights reserved.
***********************************************************************************************************************
**文件名称: error_codes.h
**功能描述: 错误定义
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
	ERROR_CODE_FAILE = -1, // 未定义/一般的错误
	ERROR_CODE_TIMEOUT = -2, // 超时
	ERROR_CODE_PARAMETER = -3, // 参数错误
	ERROR_CODE_NO_MORE_MEM = -4, // 内存不足
	ERROR_CODE_SYNC_CALL = -5, // 异步模式调用同步方法错误
	ERROR_CODE_NOT_SUPPORT = -6, // 不支持
	ERROR_CODE_NO_MORE = -7, // 没有更多
	ERROR_CODE_CLOSED = -8, // 已关闭
};


#ifdef __cplusplus
}
#endif

#endif // !__ERROR_CODES_H__
