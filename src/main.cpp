#include "main.hpp"


/** ModBusRTU性能(X3M-ttyS3)
 * 
 * 1500000
 * W1 + R1  ->334FPS
 * W58 + R86->167FPS
 * W59 + R101->166FPS
 * W121 + R125->129FPS
 * 
 * 921600 (硬件串口支持最高波特率)
 * W1 + R1  ->980FPS
 * W58 + R86->200FPS 
 * W59 + R101->167FPS
 * W121 + R125->125FPS
*/

uint16_t get_sys_time_ms(void)
{
    uint16_t time_ms = 0;
    struct timeval sys_current_time;

    gettimeofday(&sys_current_time, NULL);
    time_ms = ((uint16_t)sys_current_time.tv_sec*1000000 + sys_current_time.tv_usec) / 1000;

    return time_ms;
}





/*
** FUNCTION
* 1 --> 最高性能测试
* 2 --> 最低性能测试
* 3 --> 高频测试   
* 4 --> 低频测试   
* 5 --> 随便测试   
* 6 --> 58+86  
* 7 --> 100+86 
*/

// // 正常数据
// #define SLAVE      SLAVE_7
// #define WRITENB    WRITENUMBER_7
// #define WRITEADDR  0x01
// #define READNB     READNUMBER_7
// #define READADDR   READADDRESSH


// 调试
#define SLAVE      SLAVE_4
#define WRITENB    WRITENUMBER_5
#define WRITEADDR  WRITEADDRESS


// // 高频1
// #define READNB     74
// #define READADDR   0x03

// // 高频2
// #define READNB     14
// #define READADDR   0x01

// 低频
#define READNB     12
#define READADDR   0x02

int delta_data()
{
    uint16_t read_data[READNB] = {0};   // 存储读取数据buf
    uint16_t write_data[WRITENB] = {0}; // 存储发送数据buf

    int reg = ModBusData_Write_And_Read(SLAVE, WRITEADDRESS, WRITENB, write_data, READADDR, READNB, read_data);

    fmt::print("reg = {}\n", reg);

    if(reg != -1)
    {
        // CALC_FPS("modbus");
        
        // for (auto data : read_data)
        // {
        //     fmt::print("{:X}-{:d}\t ", data, data);
        // }
        // fmt::print("\n\n");
    }

    return 0;

}

int main(int argc, char *argv[])
{

    ModbusData_Setup("/dev/ttyUSB0", 921600);
    // modbus_t * ctx = ModbusData_Setup("/dev/ttyUSB0", 1500000);

    while(true)
    {
        delta_data();
    }

    ModbusData_Exit();

    return 0;
}


// #include <iostream>
// #include <vector>
// #include <stdio.h>
// #include <string.h>
 
// int main()
// {
//     uint32_t chip_id = 10685936;

//     std::vector<uint8_t> testvector;

//     testvector.resize(sizeof(chip_id));

//     // testvector.push_back(chip_id);

//     std::memcpy(&testvector.data()[0], &chip_id, sizeof(chip_id));

//     // 以32进制输出testvector
//     for (auto data : testvector)
//     {
//         fmt::print("{:x} - ", data);
//         fmt::print("{:d} - ", data);
//     }
//     fmt::print("\n\n");
// }
