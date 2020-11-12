#include <core/device_driver_manager.h>







void uart_debug_rx_callback(uint16_t device_id, uint8_t* buf, uint32_t size)
{
}

void uart_debug_tx_callback(uint16_t device_id)
{
}

void test_for_uart_debug()
{
    //device_driver_uart_t* uart_debug = (device_driver_uart_t*)get_device_by_id(PLATFORM_DEV_ID_UART_DEBUG, DEV_BUS_DEFAULT); // 通过ID查找设备

    /* 通过设备类型以及复用功能查找设备 */
    device_driver_uart_t* uart_debug = (device_driver_uart_t*)get_device_by_type(DEV_TYPE_UART, // 设备类型
																			UART_MUX_DEBUG, // 复用功能
																			DEV_BUS_DEFAULT); // 总线
    if (NULL == uart_debug)
    {
        return;
    }

    /* 打开设备之前注册回调 */
    uart_debug->register_rx_callback(uart_debug_rx_callback); // 注册rz回调
    uart_debug->register_tx_callback(uart_debug_tx_callback); // 注册tx发送完成回调

#if defined(_MSC_VER)

    uart_debug->open(NULL); // 使用默认参数打开

#else // VS C++不支持.fieldname初始化

	uart_cfg_parameter_t uart_para = {
        .baud_rate = 115200, // 波特率
        .data_bits = UART_DATA_8B, // 数据位
        .stop_bits = UART_STOP_1B, // 停止位
        .parity = UART_PARITY_NONE, // 校验位
        .hw_flow_ctrl = UART_HW_CTRL_NONE // 流控
    };

    uart_debug->open(&uart_para); // 使用自定义参数打开

#endif // !_MSC_VER

    /* 操作串口 */
    //uart_debug->sync_read(); // DEV_ERR_SYNC_CALL错误，原因：已注册RX回调
    //uart_debug->write();
    // ...

    uart_debug->close(&uart_debug->device);
}

void test_for_eeprom()
{
	device_driver_eeprom_t* at24C01 = (device_driver_eeprom_t*)get_device_by_type(DEV_TYPE_EEPROM,
		EEPROM_MUX_AT24C01,
		DEV_BUS_DEFAULT);
	if (NULL != at24C01)
	{
		//at24C01->sync_read();
		//at24C01->write();
		at24C01->close(&at24C01->device);
	}
}

int main()
{
    init_device_driver(); // 初始化设备总线、平台初始化、以及把平台设备挂载到总线上

    test_for_uart_debug(); // 调试串口测试

	test_for_eeprom(); // EEPROM

    return 0;
}
