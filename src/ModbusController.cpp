
#include "ModbusController.hpp"


// 数据大小端转换
uint16_t ModBusController::swapEndian_U16(uint16_t value)
{
    return (value << 8) | (value >> 8);
}


uint32_t ModBusController::swapEndian_U32(uint32_t value) {
    return ((value >> 24) & 0x000000FF) |
           ((value >> 8) & 0x0000FF00) |
           ((value << 8) & 0x00FF0000) |
           ((value << 24) & 0xFF000000);
}


int ModBusController::ModBusController_Setup(const char *device, int baud)
{
	ModBusDevice = device; ModBusBaud = baud; 

	ctx = modbus_new_rtu(device, baud, 'N', 8, 1);

	if (modbus_connect(ctx) == -1)
	{
		// fprintf(stderr, "Modbus Connection faiLED: %s\n", modbus_strerror(errno));
		modbus_free(ctx);
		// return;
	}
	
	// printf("Modbus Connection ok\n");

}


int ModBusController::ModBusController_Exit()
{
	modbus_close(ctx);
	modbus_free(ctx);
}


int ModBusController::ModBusController_Reset()
{

	ModBusController_Exit();

	ModBusController_Setup(ModBusDevice, ModBusBaud);

	return 0;
}


ModBusController::ModBusController()
{

}



ModBusController::~ModBusController()
{
	ModBusController_Exit();
}




int ModBusController::ModBusData_Write_And_Read(int slave, int write_addr, int write_nb, const uint16_t *write_data, int read_addr, int read_nb, uint16_t *read_buf)
{
	modbus_set_slave(ctx, slave);
	int datareg = modbus_write_and_read_registers(ctx, write_addr, write_nb, write_data, read_addr, read_nb, read_buf);

	if (datareg != -1){
		_CALC_FPS("modbus_write_and_read_registers");
	}

	return datareg;
}



void ModBusController::showInfo(const std::string &info, uint8_t base)
{
	if (base == 16)
	{
		fmt::print("0x{:X}\n", std::stoi(info, nullptr, 10)); // 十六进制输出
	}
	else if (base == 8)
	{
		fmt::print("0{:o}\n", std::stoi(info, nullptr, 10)); // 八进制输出
	}
	else
	{
		fmt::print("{}\n", info); // 默认输出
	}
}











