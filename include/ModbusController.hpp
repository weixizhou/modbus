
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


class ModBusAPI;
class ModBusTest;
class ModBusController;


/* API调用项
 * 
 * IMU
 * LedMode
 * Battery
 * Gamepad
 *
*/

class ModBusAPI
{

    public:

        LedData getLedRGB();

        IMUData getIMUData();

        LedData getLedMode();

        BatteryData getBatteryData();
        
        GamepadData getGamepadData();

        EspSystemStatus getEspSystemStatus();




};


/* ModBus测试项
 * 
 * ALL
 * L_1
 * H_1
 * H_2
 *
*/
class ModBusTest
{

    public:

        std::string delta_data_all();

        std::string delta_data_l_1();

        std::string delta_data_h_1();

        std::string delta_data_h_2();
        ModBusTest(ModBusController &controller) : modbuscontroller(controller) {} // 使用构造函数传入 ModBusController 的引用

    private:

        std::string ModBusTEST_ERROR = "";

        std::array<uint16_t, READNB>  Read_Data_All = {0};

        std::array<uint16_t, WRITENB> Write_Data_All  = {0};

        std::array<uint16_t, READNB_H_1>  Read_Data_H_1 = {0};

        std::array<uint16_t, WRITENB_H_1> Write_Data_H_1  = {0};

        std::array<uint16_t, READNB_H_2>  Read_Data_H_2 = {0};

        std::array<uint16_t, WRITENB_H_2> Write_Data_H_2  = {0};

        std::array<uint16_t, READNB_L_1>  Read_Data_L_1 = {0};

        std::array<uint16_t, WRITENB_L_1> Write_Data_L_1  = {0};


        ModBusController& modbuscontroller; // 保存对 ModBusController 的引用

};


/*协议控制项*/
class ModBusController
{

    friend class ModBusTest;

    public:

        ModBusTest *modbustest;

        ModBusController();

        ~ModBusController();
        ModBusController(const char *device, int baud) : modbustest(new ModBusTest(*this)){ ModBusController_Setup(device, baud); }
        
        int ModBusData_Write_And_Read(int slave, int write_addr, int write_nb, const uint16_t *write_data, int read_addr, int read_nb, uint16_t *read_buf);


        uint16_t swapEndian_U16(uint16_t value);

        uint32_t swapEndian_U32(uint32_t value);

        template <std::size_t N>
        void swapEndian_U16(std::array<uint16_t, N>& arr){
            for (std::size_t i = 0; i < N; ++i) {
                arr[i] = ((arr[i] >> 8) & 0x00FF) |
                        ((arr[i] << 8) & 0xFF00);
            }
        }

        template <std::size_t N>
        void swapEndian_U32(std::array<uint32_t, N>& arr) {
            for (auto& value : arr) {
                value = ((value >> 24) & 0x000000FF) |
                        ((value >> 8)  & 0x0000FF00) |
                        ((value << 8)  & 0x00FF0000) |
                        ((value << 24) & 0xFF000000);
            }
        }

        void showInfo(const std::string &info, uint8_t base);


    protected:

        int ModBusController_Setup(const char *device, int baud);

        int ModBusController_Reset();

        int ModBusController_Exit();


    private:

        modbus_t *ctx;

        int ModBusBaud;

        const char *ModBusDevice;

};

#endif

