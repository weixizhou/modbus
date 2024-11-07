
#ifndef MODBUSCONTROLLER_HPP
#define MODBUSCONTROLLER_HPP

#include <string>
#include <thread>
#include <cstdint>
#include <cstdint>
#include <cstring>
#include <iostream>

#define FMT_HEADER_ONLY
#include "fmt/core.h"
#include "fmt/format.h"
#include "fmt/printf.h"

#include "ModbusConfig.hpp"
#include "modbus/modbus-rtu.h"


#define _CALC_FPS(tips)                                                                                    \
{                                                                                                          \
    static int fcnt = 0;                                                                                   \
    fcnt++;                                                                                                \
    static struct timespec ts1, ts2;                                                                       \
    clock_gettime(CLOCK_MONOTONIC, &ts2);                                                                  \
    if ((ts2.tv_sec * 1000 + ts2.tv_nsec / 1000000) - (ts1.tv_sec * 1000 + ts1.tv_nsec / 1000000) >= 1000) \
    {                                                                                                      \
        printf("%s => H26X FPS:%d     \r\n", tips, fcnt);                                                  \
        ts1 = ts2;                                                                                         \
        fcnt = 0;                                                                                          \
    }                                                                                                      \
}


class ModBusAPI;
class ModBusTest;
class ModBusController;



/*API调用项*/
class ModBusAPI
{

    public:

        





};


/*单元测试项*/
class ModBusTest
{

    public:

        ModBusTest(ModBusController &controller) : modbuscontroller(controller) {} // 使用构造函数传入 ModBusController 的引用

        int delta_data();

        int delta_data_l_1();

        int delta_data_h_1();

        int delta_data_h_2();

    private:

        ModBusController& modbuscontroller; // 保存对 ModBusController 的引用

};


/*协议控制项*/
class ModBusController
{

    friend class ModBusTest; // 声明 ModBusTest 为友元类

    public:

        
        ModBusTest *modbustest;
        
        // 动态创建 modbustest 对象并传入自身引用
        ModBusController(const char *device, int baud) : modbustest(new ModBusTest(*this)) // 使用初始化列表来初始化 modbustest
        {
            ModBusController_Setup(device, baud);
        }

        ModBusController();


        ~ModBusController();

        int ModBusData_Write_And_Read(int slave, int write_addr, int write_nb, const uint16_t *write_data, int read_addr, int read_nb, uint16_t *read_buf);


    protected:



        int ModBusController_Setup(const char *device, int baud);

        int ModBusController_Reset();

        int ModBusController_Exit();


    private:

        modbus_t *ctx;

        int datareg = -1;

        int ModBusBaud;

        const char *ModBusDevice;

};


#endif

