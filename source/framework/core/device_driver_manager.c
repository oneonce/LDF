#include <core/device_driver_manager.h>
#include <core/device.h>
#include <interface/lock/mutex.h>




list_head_t g_device_bus[DEVICE_BUS_MAX];
mutex_t* g_dd_manager_lock;

void init_device_driver_bus()
{
	for (uint32_t i = 0; i < DEVICE_BUS_MAX; i++)
	{
		INIT_LIST_HEAD(&g_device_bus[i]);
	}
}

void init_device_driver()
{
	init_device_driver_bus();

	platform_init(); // 平台初始化，即把平台相关的设备挂载到总线上(调用各个驱动的init_driver_xxx)

	g_dd_manager_lock = (mutex_t*)get_device_by_type(DEVICE_TYPE_MUTEX, 0, DEVICE_BUS_DEFAULT);
}

bool is_ignore_device_type(device_t* device)
{
	if ((DEVICE_TYPE_MUTEX == device->type)
		|| (DEVICE_TYPE_GPIO == device->type) // 一个GPIO驱动可能实现多个I/O驱动，关闭某一个会导致其他I/O无法使用
		|| (DEVICE_TYPE_ADC == device->type) // ADC可能有多个通道
		|| (DEVICE_TYPE_EXT_INT == device->type) // 可能有多个外部中断s
		)
	{
		return true;
	}

	return false;
}

bool register_device_driver(list_head_t* node, enum DEVICE_BUS_ID bus_id)
{
	static uint16_t device_id_generater = 0;

	if ((NULL == node) || (DEVICE_BUS_MAX <= bus_id))
	{
		return false;
	}

	device_t* current = list_entry(node, device_t, bus_node);
	if (NULL == current)
	{
		return false;
	}

	device_t* device = NULL;
	device_t* temp = NULL;
	list_for_each_entry_safe(device, temp, &g_device_bus[bus_id], device_t, bus_node)
	{
		if ((NULL != device) && (device->id == current->id))
		{
			return false; // 重复注册
		}
	}

	if ((0 == current->id) || (DEVICE_ID_USR_BASE > current->id))
	{
		current->id = device_id_generater++;
	}

	list_add_tail(&g_device_bus[bus_id], node);

	return true;
}

void release_device_driver(device_t* device)
{
	if (NULL == device)
	{
		return;
	}

	lock();

	device->state = DEVICE_STATE_FREE; // 设置设备状态空闲

	unlock();
}

void* get_device_by_id(uint16_t id, enum DEVICE_BUS_ID bus_id)
{
	device_t* device = NULL;
	device_t* temp = NULL;

	lock();

	do
	{
		list_for_each_entry_safe(device, temp, &g_device_bus[bus_id], device_t, bus_node)
		{
			if ((NULL == device) || (DEVICE_STATE_INUSE == device->state))
			{
				continue;
			}

			if (device->id == id)
			{
				if (!is_ignore_device_type(device))
				{
					device->state = DEVICE_STATE_INUSE; // 设备使用中
				}

				break;
			}

			device = NULL;
		}
	} while (0);

	unlock();

	return device;
}

void* get_device_by_type(enum DEVICE_TYPE type, uint32_t multiplex, enum DEVICE_BUS_ID bus_id)
{
	device_t* device = NULL;
	device_t* temp = NULL;

	if (DEVICE_BUS_MAX <= bus_id)
	{
		return NULL;
	}

	lock();

	do
	{
		list_for_each_entry_safe(device, temp, &g_device_bus[bus_id], device_t, bus_node)
		{
			if ((NULL == device) || (DEVICE_STATE_INUSE == device->state))
			{
				continue;
			}

			/*[[unlikely]]*/if (0 == multiplex)
			{
				if ((type == device->type) && (multiplex == device->multiplex))
				{
					if (!is_ignore_device_type(device))
					{
						device->state = DEVICE_STATE_INUSE; // 设备使用中
					}
					break;
				}
			}
			else
			{
				if ((type == device->type) && ((multiplex & device->multiplex) == multiplex))
				{
					if (!is_ignore_device_type(device))
					{
						device->state = DEVICE_STATE_INUSE; // 设备使用中
					}
					break;
				}
			}

			device = NULL;
		}
	} while (0);

	unlock();

	return device;
}

void lock()
{
	if (NULL != g_dd_manager_lock)
	{
		g_dd_manager_lock->lock();
	}
}

bool trylock()
{
	if (NULL != g_dd_manager_lock)
	{
		if (NULL == g_dd_manager_lock->trylock)
		{
			g_dd_manager_lock->lock();
		}
		else
		{
			return g_dd_manager_lock->trylock();
		}
	}

	return true;
}

void unlock()
{
	if (NULL != g_dd_manager_lock)
	{
		g_dd_manager_lock->unlock();
	}
}
