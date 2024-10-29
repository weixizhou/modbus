#include "main.hpp"

// 本工程用到了fmt--> sudo apt install libfmt-dev

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

/** ModBusRTU性能(X3M-ttyUSB0)
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


// Platform-specific function to get current ticks (milliseconds)
uint64_t getPlatformTicks() {
    struct timeval now;
    gettimeofday(&now, NULL);
    return now.tv_sec * 1000LL + now.tv_usec / 1000;
}


// 数据一次性收发
int delta_data()
{
    uint16_t read_data[READNB] = {0};    // 存储读取数据buf
    uint16_t write_data[WRITENB] = {0};  // 存储发送数据buf

    int reg_H_1 = ModBusData_Write_And_Read(SLAVE, WRITEADDR, WRITENB, write_data, READADDR, READNB, read_data);

    fmt::print("reg_H_1 = {}\n", reg_H_1);
    
    // for (auto data : read_data)
    // {
    //     fmt::print("{:X}-{:d}\t ", data, data);
    // }
    // fmt::print("\n\n");

    return 0;
}



// 高频1
int delta_data_h_1()
{
    uint16_t read_data[READNB_H_1] = {0};    // 存储读取数据buf
    uint16_t write_data[WRITENB_H_1] = {0}; // 存储发送数据buf

    int reg_H_1 = ModBusData_Write_And_Read(SLAVE_HL, WRITEADDR_H_1, WRITENB_H_1, write_data, READADDR_H_1, READNB_H_1, read_data);

    fmt::print("reg_H_1 = {}\n", reg_H_1);
    
    // for (auto data : read_data)
    // {
    //     fmt::print("{:X}-{:d}\t ", data, data);
    // }
    // fmt::print("\n\n");

    return 0;

}


// 高频2
int delta_data_h_2()
{
    uint16_t read_data_[READNB_H_2] = {0};    // 存储读取数据buf
    uint16_t write_data_[WRITENB_H_2] = {0}; // 存储发送数据buf
    
    int reg_H_2 = ModBusData_Write_And_Read(SLAVE_HL, WRITEADDR_H_2, WRITENB_H_2, write_data_, READADDR_H_2, READNB_H_2, read_data_);

    fmt::print("reg_H_2 = {}\n", reg_H_2);

    
    // for (auto data : read_data)
    // {
    //     fmt::print("{:X}-{:d}\t ", data, data);
    // }
    // fmt::print("\n\n");

    return 0;

}


// 低频1
int delta_data_l_1()
{
    uint16_t read_data__[READNB_L_1] = {0};  // 存储读取数据buf
    uint16_t write_data__[WRITENB_L_1] = {0}; // 存储发送数据buf
    
    int reg_L_1 = ModBusData_Write_And_Read(SLAVE_HL, WRITEADDR_L_1, WRITENB_L_1, write_data__, READADDR_L_1, READNB_L_1, read_data__);

    fmt::print("reg_L_1 = {}\n", reg_L_1);

    // for (auto data : read_data)
    // {
    //     fmt::print("{:X}-{:d}\t ", data, data);
    // }
    // fmt::print("\n\n");
    
    return 0;

}


int main(int argc, char *argv[])
{

    ModbusData_Setup("/dev/ttyUSB1", 1500000);
    // ModbusData_Setup("/dev/ttyUSB1", 921600);

    uint64_t last_time = getPlatformTicks();

    while(true)
    {

        // delta_data();

        // delta_data_h_1();

        // delta_data_h_2();

        if (getPlatformTicks()  - last_time > 3000)
        {
            // delta_data_l_1();

            last_time = getPlatformTicks();
        }

    }

    ModbusData_Exit();

    return 0;
}
