
#include "ModbusController.hpp"

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
std::string ModBusTest::delta_data_all()
{

	Write_Data_All = tmp;

	int reg = modbuscontroller.ModBusData_Write_And_Read(SLAVE, WRITEADDR, Write_Data_All.size(), Write_Data_All.data(), READADDR, Read_Data_All.size(), Read_Data_All.data());
	
	#ifdef TEST_REG_
		fmt::print("delta_data_all reg = {}\n", reg);
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
std::string ModBusTest::delta_data_h_1()
{
	Write_Data_H_1 = tmp;

	int reg_H_1 = modbuscontroller.ModBusData_Write_And_Read(SLAVE_HL, WRITEADDR_H_1, Write_Data_H_1.size(), Write_Data_H_1.data(), READADDR_H_1, Read_Data_H_1.size(), Read_Data_H_1.data());


	#ifdef TEST_REG
		fmt::print("delta_data_h_1 reg = {}\n", reg_H_1);
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
std::string ModBusTest::delta_data_h_2()
{

	int reg_H_2 = modbuscontroller.ModBusData_Write_And_Read(SLAVE_HL, WRITEADDR_H_2, Write_Data_H_2.size(), Write_Data_H_2.data(), READADDR_H_2, Read_Data_H_2.size(), Read_Data_H_2.data());


	modbuscontroller.swapEndian_U16(Read_Data_H_2);


	#ifdef TEST_REG
		fmt::print("delta_data_h_1 reg = {}\n", reg_H_2);
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
std::string ModBusTest::delta_data_l_1()
{

	int reg_L_1 = modbuscontroller.ModBusData_Write_And_Read(SLAVE_HL, WRITEADDR_L_1, Write_Data_L_1.size(), Write_Data_L_1.data(), READADDR_L_1, Read_Data_L_1.size(), Read_Data_L_1.data());

	modbuscontroller.swapEndian_U16(Read_Data_L_1);

	#ifdef TEST_REG
		fmt::print("delta_data_l_1 reg = {}\n", reg_L_1);
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




