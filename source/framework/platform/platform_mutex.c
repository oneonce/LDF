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


mutex_t g_plat_mutex =
{
	.device = {
		.id = 0,
		.type = DEVICE_TYPE_MUTEX,
		.state = DEVICE_STATE_FREE,
		.bus_id = DEVICE_BUS_DEFAULT,
		.multiplex = 0, //
	},
	.lock = platform_lock,
	//.trylock = platform_trylock,
	.unlock = platform_unlock,
};


void register_plat_lock()
{
	register_device_driver(&g_plat_mutex.device.bus_node, g_plat_mutex.device.bus_id);
}
