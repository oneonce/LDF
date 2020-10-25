#include <core/device_manager.h>
#include <core/device.h>




list_head_t g_device_bus[DEV_BUS_MAX];


void init_device_driver_bus()
{
	for (uint32_t i = 0; i < DEV_BUS_MAX; i++)
	{
		INIT_LIST_HEAD(&g_device_bus[i]);
	}
}

void init_device_driver()
{
	init_device_driver_bus();

	platform_init(); // 平台初始化，即把平台相关的设备挂载到总线上(调用各个驱动的init_driver_xxx)
}

bool register_device(list_head_t* node, enum DEVICE_BUS_ID bus_id)
{
	static uint16_t device_id_generater = 0;

	if ((NULL == node) || (DEV_BUS_MAX <= bus_id))
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

	//current->state = DEV_STATE_FREE; // 注册时设置设备为空闲状态?

	list_add_tail(&g_device_bus[bus_id], node);

	return true;
}

void* get_device_by_id(uint16_t id, enum DEVICE_BUS_ID bus_id)
{
	device_t* device = NULL;
	device_t* temp = NULL;

	list_for_each_entry_safe(device, temp, &g_device_bus[bus_id], device_t, bus_node)
	{
		if ((NULL == device) || (DEV_STATE_USING == device->state))
		{
			continue;
		}

		if (device->id == id)
		{
            device->state = DEV_STATE_USING; // 设备使用中
			return device;
		}
	}

	return NULL;
}

void* get_device_by_type(enum DEVICE_TYPE type, uint32_t multiplex, enum DEVICE_BUS_ID bus_id)
{
	device_t* device = NULL;
	device_t* temp = NULL;

	if (DEV_BUS_MAX <= bus_id)
	{
		return NULL;
	}

	list_for_each_entry_safe(device, temp, &g_device_bus[bus_id], device_t, bus_node)
	{
		if ((NULL == device) || (DEV_STATE_USING == device->state))
		{
			continue;
		}

		/*[[unlikely]]*/if (0 == multiplex)
		{
			if ((type == device->type) && (multiplex == device->multiplex))
			{
				device->state = DEV_STATE_USING; // 设备使用中
				return device;
			}
		}
		else
		{
			if ((type == device->type) && ((multiplex & device->multiplex) == multiplex))
			{
				device->state = DEV_STATE_USING; // 设备使用中
				return device;
			}
		}
	}

	return NULL;
}
