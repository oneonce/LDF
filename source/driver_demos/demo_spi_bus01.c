#include "demo_spi_bus01.h"
#include <core/device_driver_manager.h>






static void spi_bus01_open(spi_cfg_parameter_t* cfg_parameter)
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

static void spi_bus01_close(device_t* device)
{
	release_device_driver(device); // 调用驱动管理释放设备
}

static void spi_bus01_pin_level_ctrl(enum SPI_SIGNAL_PIN pin, enum IO_LEVEL_EDGE level)
{
	switch (pin)
	{
	case SPI_SIGNAL_PIN_CS: // cs
		break;
	case SPI_SIGNAL_PIN_CLK: // clk
		break;
	case SPI_SIGNAL_PIN_MOSI: // mosi
		break;
	case SPI_SIGNAL_PIN_MISO: // miso
		break;
	default:
		break;
	}
}

static int32_t spi_bus01_transfer(spi_message_t* msg, int32_t msg_cnt, const uint32_t millisecond)
{
	if ((NULL == msg) || (0 == msg_cnt))
	{
		return ERROR_CODE_PARAMETER;
	}

	for (int32_t msg_id = 0; msg_id < msg_cnt; msg_id++)
	{
		if (SPI_FLG_CS_START_KEEP == msg[msg_id].cs_flg)
		{
			// 无CS操作
		}
		else if (SPI_FLG_CS_START_OPEN == (msg[msg_id].cs_flg & SPI_FLG_CS_START_OPEN))
		{
			// 打开片选
		}

		/* 传输数据 */
		/* write */
		for (int32_t data_id = 0; data_id < msg[msg_id].tx_length; data_id++)
		{
			// reg = msg[msg_id].tx_buffer[data_id];
		}

		/* read */
		// memcpy(msg[msg_id].rx_buffer, ...);

		if (SPI_FLG_CS_END_KEEP == (msg[msg_id].cs_flg & SPI_FLG_CS_END_KEEP))
		{
			// 无CS操作
		}
		else if (SPI_FLG_CS_END_CLOSE == (msg[msg_id].cs_flg & SPI_FLG_CS_END_CLOSE))
		{
			// 关闭片选
		}
	}

	return 0;
}

device_driver_spi_t spi_bus01 =
{
	.device = {
		//.id = DEVICE_ID_SPI_BUS01, // 使用自定义ID，参考platform.h
		.id = 0, // 为0时由设备管理自动分配ID，>=DEVICE_ID_USR_BASE为自定义ID
		.state = DEVICE_STATE_FREE, // 空闲状态
		.use_mode = DEVICE_USE_MODE_EXCLUSIVE, // 独占模式
		.type = DEVICE_TYPE_SPI, // SPI总线类型
		.bus_id = DEVICE_BUS_DEFAULT, // 挂载默认总线上
		.multiplex = SPI_MUX_BUS_01, // SPI总线编号01
	},
	.open = spi_bus01_open,
	.close = spi_bus01_close,
	.pin_level_ctrl = spi_bus01_pin_level_ctrl,
	.transfer = spi_bus01_transfer,
};

void init_demo_spi_bus01()
{
	register_device_driver(&spi_bus01.device.bus_node, spi_bus01.device.bus_id);
}
