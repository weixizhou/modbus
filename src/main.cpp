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


#define SLAVE      SLAVE_7
#define READADDR   READADDRESSH
#define WRITEADDR  WRITEADDRESS
#define READNB     READNUMBER_7
#define WRITENB    WRITENUMBER_7

void delta_data()
{
    uint16_t read_data[READNB] = {0};   // 存储读取数据buf
    uint16_t write_data[WRITENB] = {0}; // 存储发送数据buf

    int reg = ModBusData_Write_And_Read(SLAVE, WRITEADDRESS, WRITENB, write_data, READADDR, READNB, read_data);
    fmt::print("high speed reg = {}\n", reg);

    reg = ModBusData_Write_And_Read(SLAVE, WRITEADDRESS, WRITENB, write_data, READADDRESSL, 1, read_data);
    fmt::print("low speed reg = {}\n\n", reg);

    // if(reg != -1)
    // {
    //     CALC_FPS("modbus");
        
    //     for (int i = 0; i < 100; i++)
    //     {
    //         fmt::print("data {} = {}\n", i, read_data[i]);
    //     }
    //     fmt::print("\n");
    // }

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