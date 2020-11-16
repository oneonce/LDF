#include <platform/platform_mutex.h>
#include <core/device_driver_manager.h>




static void platform_lock()
{
	// 具体实现
}

//static bool platform_trylock()
//{
//	return false;
//}

static void platform_unlock()
{
	// 具体实现
}

static uint32_t platform_get_resource_total_count()
{
	return 0xFFFFFFFF;
}

static uint32_t platform_get_resource_free_count()
{
	return 0xFFFFFFFE;
}



mutex_t g_plat_mutex =
{
	.device = {
		.id = 0,
		.state = DEVICE_STATE_FREE,
		.use_mode = DEVICE_USE_MODE_SHARED, // 共享模式
		.type = DEVICE_TYPE_MUTEX,
		.bus_id = DEVICE_BUS_DEFAULT,
		.multiplex = 0, //
		.get_resource_total_count = platform_get_resource_total_count,
		.get_resource_free_count = platform_get_resource_free_count,
	},
	.lock = platform_lock,
	//.trylock = platform_trylock,
	.unlock = platform_unlock,
};


void register_plat_lock()
{
	register_device_driver(&g_plat_mutex.device.bus_node, g_plat_mutex.device.bus_id);
}
