
#include "ModbusREG.hpp"
#include "modbus/modbus-rtu.h"

/*初始化Modbus -->串口号 波特率*/
modbus_t *ModbusData_Setup(const char *device, int baud);

/*退出Modbus*/
int ModbusData_Exit(/*modbus_t *ctx*/);

/*重置Modbus*/
int ModbusData_Reset(/*modbus_t *ctx*/);

// // 两位uint16转float
float uint16ToFloat(uint16_t low, uint16_t high);

std::tuple<uint16_t, uint16_t> float_to_uint16(float value);

/* 全部数据一次性读写  [先写后读]*/
int ModBusData_Write_And_Read(int slave, int write_addr, int write_nb, const uint16_t *write_data, int read_addr, int read_nb, uint16_t *read_buf);

// ===================================================================

