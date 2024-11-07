
#include "ModbusController.hpp"



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














