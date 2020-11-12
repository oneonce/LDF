#include "driver_uart_debug.h"
#include <core/device_driver_manager.h>





uart_rx_callback uart_debug_rx_callback = NULL;
uart_tx_callback uart_debug_tx_callback = NULL;

uint16_t g_uar_debug_id = 0;

void uart_debug_open(uart_cfg_parameter_t* cfg_parameter)
{
    if (NULL == cfg_parameter)
    {
        // 设置默认参数
    }
    else
    {
        // 根据parameter参数设置
    }
}

static void uart_debug_close(device_t* device)
{
    if (NULL != device)
    {
        device->state = DEV_STATE_FREE; // 设置设备状态空闲
    }
}

static int32_t uart_debug_sync_read(uint8_t* buffer, const int32_t buffer_size, const uint32_t millisecond)
{
    if (NULL != uart_debug_rx_callback) // 已注册RX回调
    {
        return DEV_ERR_SYNC_CALL; // 同步调用错误
    }

    return 0;
}

static int32_t uart_debug_write(const uint8_t* buffer, const int32_t buffer_size, const uint32_t millsecond)
{
    return 0;
}

static void uart_debug_register_rx_callback(uart_rx_callback callback)
{
    uart_debug_rx_callback = callback;
}

static void uart_debug_register_tx_callback(uart_tx_callback callback)
{
    uart_debug_tx_callback = callback;
}


#if 1 // 初始化方式1(有的编译工具不支持)

device_driver_uart_t uart_debug =
{
    .device = {
        .id = PLATFORM_DEV_ID_UART_DEBUG, // 使用自定义ID，参考platform.h
        //.id = 0, // 为0时由设备管理自动分配ID，>=DEVICE_ID_USR_BASE为自定义ID
        .type = DEV_TYPE_UART, // 串口类型
        .state = DEV_STATE_FREE, // 空闲状态
        .bus_id = DEV_BUS_DEFAULT, // 挂载默认总线上
        .multiplex = UART_MUX_DEBUG, // 调试串口
    },
    .open = uart_debug_open,
    .close = uart_debug_close,
    .sync_read = uart_debug_sync_read,
    .write = uart_debug_write,
    .register_rx_callback = uart_debug_register_rx_callback,
    .register_tx_callback = uart_debug_register_tx_callback,
};

#else // 初始化方式2

device_driver_uart_t uart_debug;

void init_driver_attr() // 在init_driver_uart_debug()中调用
{
        uart_debug.device.id = PLATFORM_DEV_ID_UART_DEBUG, // 使用自定义ID，参考platform.h
        //uart_debug.device.id = 0; // 为0时由设备管理自动分配ID，>=DEVICE_ID_USR_BASE为自定义ID
        uart_debug.device.type = DEV_TYPE_UART, // 串口类型
        uart_debug.device.state = DEV_STATE_FREE; // 空闲状态
        uart_debug.device.bus_id = DEV_BUS_DEFAULT; // 挂载默认总线上
        uart_debug.device.multiplex = UART_MUX_DEBUG; // 调试串口

        uart_debug.open = uart_debug_open;
        uart_debug.close = uart_debug_close;
        uart_debug.sync_read = uart_debug_sync_read;
        uart_debug.write = uart_debug_write;
        uart_debug.register_rx_callback = uart_debug_register_rx_callback;
        uart_debug.register_tx_callback = uart_debug_register_tx_callback;
}

#endif


// 设备注册注册过程: main->init_device_driver(device_manager.c)->platform_init(platform.c)->init_driver_uart_debug
void init_driver_uart_debug()
{
    // init_driver_attr(); // 初始化方式2

    register_device_driver(&uart_debug.device.bus_node, uart_debug.device.bus_id);

	g_uar_debug_id = uart_debug.device.id;
}
