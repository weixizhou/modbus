
#include "ModbusController.hpp"

// ModBusTest::ModBusTest(ModBusController &modbuscontroller) : modbuscontroller(modbuscontroller) { }


// 数据一次性收发
int ModBusTest::delta_data()
{
	uint16_t read_data[READNB] = {0}; // 存储读取数据buf

	uint16_t write_data[WRITENB_H_1] = {2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047,\
										200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, \
										0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
										40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, \
										2, 0};

	// uint16_t write_data[WRITENB] = {2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047,\
	//                                 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000,\
	//                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,\
	//                                 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000,\
	//                                 2, 0};

	int reg = modbuscontroller.ModBusData_Write_And_Read(SLAVE, WRITEADDR, WRITENB, write_data, READADDR, READNB, read_data);

	fmt::print("reg = {}\n", reg);

	// // 电机数据
	// for (int i = 30; i <= 85; i++)
	// {
	// 	fmt::print("{:d}\t ", read_data[i]);
	// }
	// fmt::print("\n\n");

	for (auto data : read_data)
	{
		fmt::print("{:X}-{:d}\t ", data, data);
	}
	fmt::print("\n\n");

	return 0;
}


// 高频1
int ModBusTest::delta_data_h_1()
{
	uint16_t read_data[READNB_H_1] = {0};   // 存储读取数据buf    
	
	// uint16_t write_data[WRITENB_H_1] = {2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047,\
	//                                 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, \
	//                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
	//                                 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, \
	//                                 2, 0};

	uint16_t write_data[WRITENB_H_1] = {2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, 2047, \
									1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, \
									200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, \
									40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, 40000, \
									2, 0};

	int reg_H_1 = modbuscontroller.ModBusData_Write_And_Read(SLAVE_HL, WRITEADDR_H_1, WRITENB_H_1, write_data, READADDR_H_1, READNB_H_1, read_data);

	fmt::print("reg_H_1 = {}\n", reg_H_1);

	for (auto data : read_data)
	{
		// fmt::print("{:X}-{:d}\t ", data, data);
		fmt::print("{}\t ", data);
	}
	fmt::print("\n\n");

	return 0;
}


// 高频2
int ModBusTest::delta_data_h_2()
{
	std::array<uint16_t, READNB_H_2>  read_data_ = {0};   // 存储读取数据buf
	std::array<uint16_t, WRITENB_H_2> write_data_ = {0};   // 存储读取数据buf

	int reg_H_2 = modbuscontroller.ModBusData_Write_And_Read(SLAVE_HL, WRITEADDR_H_2, WRITENB_H_2, write_data_.data(), READADDR_H_2, READNB_H_2, read_data_.data());

	fmt::print("reg_H_2 = {}\n", reg_H_2);

	for (auto data : read_data_)
	{
		// fmt::print("{:X}-{:d}\t ", data, data);
		fmt::print("{:d}\t ", data);
	}
	fmt::print("\n");


	std::array<uint8_t, read_data_.size()*2> read_data_U8 = {0};

	// 把read_data_数据拷贝给read_data_U8
	memcpy(&read_data_U8, read_data_.data(), (sizeof(read_data_)));

	fmt::print("\nU8\n");
	for (auto data : read_data_U8)
	{
		fmt::print("{:d}\t ", data);
	}
	fmt::print("\n\n\n");    


	return 0;
}


// 低频1
int ModBusTest::delta_data_l_1()
{
	uint16_t read_data__[READNB_L_1] = {0};   // 存储读取数据buf
	uint16_t write_data__[WRITENB_L_1] = {0}; // 存储发送数据buf

	int reg_L_1 = modbuscontroller.ModBusData_Write_And_Read(SLAVE_HL, WRITEADDR_L_1, WRITENB_L_1, write_data__, READADDR_L_1, READNB_L_1, read_data__);

	fmt::print("reg_L_1 = {}\n", reg_L_1);

	// for (auto data : read_data)
	// {
	//     fmt::print("{:X}-{:d}\t ", data, data);
	// }
	// fmt::print("\n\n");

	return 0;
}




