
#include <string>
#include <thread>
#include <cstring>
#include <iostream>
#include <cstdint>
#include "ModbusData.h"
#include <iomanip> // 用于 std::setw


using namespace std;

/*Modbus实例*/
modbus_t *ctx;
/*设置的波特率*/
static int ModBusBaud;
/*设置的串口号*/
static const char *ModBusDevice;

/*所有数据reg*/
int datareg = -1;

#define _CALC_FPS(tips)                                                                                         \
	{                                                                                                          \
		static int fcnt = 0;                                                                                   \
		fcnt++;                                                                                                \
		static struct timespec ts1, ts2;                                                                       \
		clock_gettime(CLOCK_MONOTONIC, &ts2);                                                                  \
		if ((ts2.tv_sec * 1000 + ts2.tv_nsec / 1000000) - (ts1.tv_sec * 1000 + ts1.tv_nsec / 1000000) >= 1000) \
		{                                                                                                      \
			printf("%s => H26X FPS:%d     \r\n", tips, fcnt);                                             \
			ts1 = ts2;                                                                                         \
			fcnt = 0;                                                                                          \
		}                                                                                                      \
	} // 一秒内程序被调用的次数累加实现


uint32_t GetSystemTime()
{
	// 获取当前系统时间
	static struct timespec tmp;
	clock_gettime(CLOCK_MONOTONIC, &tmp);
	return (tmp.tv_sec * 1000) + (uint32_t)tmp.tv_nsec / 1000000;
}



/*初始化Modbus -->串口号 波特率*/
modbus_t *ModbusData_Setup(const char *device, int baud)
{
	ModBusBaud = baud;
	ModBusDevice = device;


	// 初始化Modbus实例
	ctx = modbus_new_rtu(device, baud, 'N', 8, 1);
	if (modbus_connect(ctx) == -1)
	{
		// fprintf(stderr, "Modbus Connection faiLED: %s\n", modbus_strerror(errno));
		modbus_free(ctx);
		return ctx;
	}
	else
	{
		// printf("Modbus Connection ok\n");
		return ctx;
	}
}

/* 全部数据一次性读写  [先写后读]*/
int ModBusData_Write_And_Read(int slave, int write_addr, int write_nb, const uint16_t *write_data, int read_addr, int read_nb, uint16_t *read_buf)
{
	modbus_set_slave(ctx, slave);
	int datareg = modbus_write_and_read_registers(ctx, write_addr, write_nb, write_data, read_addr, read_nb, read_buf);

	if (datareg != -1){
		_CALC_FPS("modbus_write_and_read_registers");
	}

	return datareg;
}

/*退出Modbus*/
int ModbusData_Exit(/*modbus_t *ctx*/)
{
	modbus_close(ctx);
	modbus_free(ctx);

	return 0;
}

/*重置Modbus*/
int ModbusData_Reset(/*modbus_t *ctx*/)
{
	ModbusData_Exit(/*modbus_t *ctx*/);
	ModbusData_Setup(ModBusDevice, ModBusBaud);

	return 0;
}
