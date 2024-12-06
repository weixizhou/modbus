
#include "ModBusRTUController.hpp"


// ModBusRTUController::ModBusRTUController()
// {

// }



// ModBusRTUController::~ModBusRTUController()
// {
// 	ModBusRTU_Exit();
// }



int ModBusRTUController::ModBusRTU_Setup(const char *device, int baud)
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


int ModBusRTUController::ModBusRTU_Exit()
{
	modbus_close(ctx);
	modbus_free(ctx);
}


int ModBusRTUController::ModBusRTU_Reset()
{

	ModBusRTU_Exit();

	ModBusRTU_Setup(ModBusDevice, ModBusBaud);

	return 0;
}





int ModBusRTUController::ModBusRTU_Write_And_Read(int slave, int write_addr, int write_nb, const uint16_t *write_data, int read_addr, int read_nb, uint16_t *read_buf)
{
	modbus_set_slave(ctx, slave);
	int datareg = modbus_write_and_read_registers(ctx, write_addr, write_nb, write_data, read_addr, read_nb, read_buf);

	if (datareg != -1){
		_CALC_FPS("modbus_write_and_read_registers");
	}

	return datareg;
}







// 数据大小端转换
uint16_t ModBusRTUController::swapEndian_U16(uint16_t value)
{
    return (value << 8) | (value >> 8);
}


uint32_t ModBusRTUController::swapEndian_U32(uint32_t value) {
    return ((value >> 24) & 0x000000FF) |
           ((value >> 8) & 0x0000FF00) |
           ((value << 8) & 0x00FF0000) |
           ((value << 24) & 0xFF000000);
}




// =======================================================测试项=======================================================================


// std::array<uint16_t, 58>  tmp = { 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047,\
// 										0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
// 										0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
// 										40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, \
// 										2, 0};
std::array<uint16_t, 58>  tmp = { 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047,\
										200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, \
										0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
										40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, \
										2, 0};

// std::array<uint16_t, 58>  tmp = { 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, \
// 										1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, \
// 										200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, \
// 										40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, \
// 										2, 0};


// std::array<uint16_t, 58>  tmp = { 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, \
// 										1000, 0, 0, 1000, 0, 0, 1000, 0, 0, 1000, 0, 0, 200, 200, \
// 										200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, \
// 										40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, \
// 										2, 0};

// 数据一次性收发
std::string ModBusRTUController::ModBusRTU_Test_Data_All()
{

	Write_Data_All = tmp;

	int Reg = ModBusRTU_Write_And_Read(SLAVE, WRITEADDR, Write_Data_All.size(), Write_Data_All.data(), READADDR, Read_Data_All.size(), Read_Data_All.data());
	
	#ifdef TEST_REG_
		fmt::print("ModBusRTU_Test_Data_All Reg = {}\n", Reg);
	#endif

	#ifdef TEST_DEBUG_
		std::string str;
			for (uint8_t i = 0; i < Read_Data_All.size(); i++)
			{
				str += std::to_string(Read_Data_All.at(i));
				i == (Read_Data_All.size()-1) ? str += "\n" : str += ", ";
			}
		return str;
	#else
		return ModBusTEST_ERROR;
	#endif



}


// 高频1
std::string ModBusRTUController::ModBusRTU_Test_Data_H_1()
{
	Write_Data_H_1 = tmp;

	int reg_H_1 = ModBusRTU_Write_And_Read(SLAVE_HL, WRITEADDR_H_1, Write_Data_H_1.size(), Write_Data_H_1.data(), READADDR_H_1, Read_Data_H_1.size(), Read_Data_H_1.data());


	#ifdef TEST_REG
		fmt::print("ModBusRTU_Test_Data_H_1 Reg = {}\n", reg_H_1);
	#endif


	#ifdef TEST_DEBUG
		std::string str;
			for (uint8_t i = 0; i < Read_Data_H_1.size(); i++)
			{
				str += std::to_string(Read_Data_H_1.at(i));
				i == (Read_Data_H_1.size()-1) ? str += "\n" : str += ", ";
			}
		return str;
	#else
		return ModBusTEST_ERROR;
	#endif
}


// 高频2
std::string ModBusRTUController::ModBusRTU_Test_Data_H_2()
{

	int reg_H_2 = ModBusRTU_Write_And_Read(SLAVE_HL, WRITEADDR_H_2, Write_Data_H_2.size(), Write_Data_H_2.data(), READADDR_H_2, Read_Data_H_2.size(), Read_Data_H_2.data());


	swapEndian_U16(Read_Data_H_2);


	#ifdef TEST_REG
		fmt::print("ModBusRTU_Test_Data_H_2 Reg = {}\n", reg_H_2);
	#endif

	#ifdef TEST_DEBUG
		std::string str;
			for (uint8_t i = 0; i < Read_Data_H_2.size(); i++)
			{
				str += std::to_string(Read_Data_H_2.at(i));
				i == (Read_Data_H_2.size()-1) ? str += "\n" : str += ", ";
			}
		return str;
	#else
		return ModBusTEST_ERROR;
	#endif

}


// 低频1
std::string ModBusRTUController::ModBusRTU_Test_Data_L_1()
{

	int reg_L_1 = ModBusRTU_Write_And_Read(SLAVE_HL, WRITEADDR_L_1, Write_Data_L_1.size(), Write_Data_L_1.data(), READADDR_L_1, Read_Data_L_1.size(), Read_Data_L_1.data());

	swapEndian_U16(Read_Data_L_1);

	#ifdef TEST_REG
		fmt::print("ModBusRTU_Test_Data_L_1 Reg = {}\n", reg_L_1);
	#endif

	#ifdef TEST_DEBUG
		std::string str;
			for (uint8_t i = 0; i < Read_Data_L_1.size(); i++)
			{
				str += std::to_string(Read_Data_L_1.at(i));
				i == (Read_Data_L_1.size()-1) ? str += "\n" : str += ", ";
			}
		return str;
	#else
		return ModBusTEST_ERROR;
	#endif

}








