
  LDF是一套适用于单片机驱动开发的轻量级框架，其参考了linux总线相关的设计思想，同时其总线同样使用linux的list_head(做了部分修改和裁剪)，LDF的设计非常简单，代码量很少。
  LDF针对不同的外设有不同的驱动接口，大部分驱动接口都有read/write方法，但不同的外设驱动read/write的形参也不一定相同，之所以对具体外设进行接口化主要是对业务层更透明，不使用ioctl的原因是驱动层定义不同的cmd可能其他参数或类型不一定相同，对业务层造成一定的困惑（或增加沟通成本，因为业务层不需要懂驱动）。
  
  

********************************************************** 目录介绍 *********************************************************

1. LDF中包含了core、interface、platform、driver_demos、utils等目录：
  1.1 core
    core目录包含了LDF驱动相关的核心部分代码
  1.2. interface
    interface主要用于对外设驱动接口定义
  1.3. platform
    plaform主要用于框架和平台之间的衔接，所有外设驱动头文件都将包含在platform.c文件中，并由platform_init()进行调用。
    注：该部分外设驱动初始化函数需要开发人员进行处理。
  1.4. utils
    该目录包含驱动框架使用的辅助工具(如list_head)
  1.5. driver_demos
    该目录主要对interface中定义的外设驱动进行使用颜色，但并不涉及到真正的驱动代码(如设置时钟、寄存器、中断...)
 
 
 
 
**********************************************************外设驱动 **********************************************************
  
  1. UART驱动演示
    
    1.1 driver_uart_debug.h
    
    
    
    
      #ifndef __DRIVER_UART_DEBUG_H__
      #define __DRIVER_UART_DEBUG_H__

      #ifdef __cplusplus
      extern "C" {
      #endif

      void init_driver_uart_debug();

      #ifdef __cplusplus
      }
      #endif

      #endif // !__DRIVER_UART_DEBUG_H__
  
  
  
  
  
    1.2 driver_uart_debug.c
    
    
    
    
      #include "driver_uart_debug.h"
      #include <core/device_manager.h>



      uart_rx_callback uart_debug_rx_callback = NULL;
      uart_tx_callback uart_debug_tx_callback = NULL;


      void uart_debug_open(uart_parameter_t* parameter)
      {
          if (NULL == parameter)
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

      driver_uart_t uart_debug =
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

      // 设备注册注册过程: main->init_device_driver(device_manager.c)->platform_init(platform.c)->init_driver_uart_debug
      void init_driver_uart_debug()
      {
          register_device(&uart_debug.device.bus_node, uart_debug.device.bus_id);
      }
  

 ********************************************************** 使用演示 **********************************************************
 
  
 1. UAR使用实例
 
 
    
    #include <core/device_manager.h>
  
    //driver_uart_t* uart_debug = (driver_uart_t*)get_device_by_id(PLATFORM_DEV_ID_UART_DEBUG, DEV_BUS_DEFAULT); // 通过ID查找设备

    driver_uart_t* uart_debug = (driver_uart_t*)get_device_by_type(DEV_TYPE_UART, UART_MUX_DEBUG, DEV_BUS_DEFAULT); // 通过设备类型以及复用功能查找设备
    
    if (NULL == uart_debug)
    {
        return; // 获取串口设备失败
    }

    /* 打开设备之前注册回调 */
    
    uart_debug->register_rx_callback(uart_debug_rx_callback); // 注册RX回调
    
    uart_debug->register_tx_callback(uart_debug_tx_callback); // 注册TX回调

  #if defined(_MSC_VER)

    uart_debug->open(NULL); // 使用默认参数打开

  #else // VS C++不支持.fieldname初始化

    uart_parameter_t uart_para = {
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

  
