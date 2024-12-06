
#ifndef ModBusRTUController_HPP
#define ModBusRTUController_HPP

#include <string>
#include <thread>
#include <vector>
#include <cstdint>
#include <cstdint>
#include <cstring>
#include <iostream>

#define FMT_HEADER_ONLY
#include "fmt/core.h"
#include "fmt/format.h"
#include "fmt/printf.h"

#include "ModBusRTUConfig.hpp"
#include "modbus/modbus-rtu.h"


/*ModBus协议控制项*/
class ModBusRTUController
{

    public:


        int ModBusRTU_Setup(const char *device, int baud);

        int ModBusTCP_Setup(const char * ssid, const char * pwd, int port);



        int ModBusRTU_Reset();

        int ModBusRTU_Exit();



        int ModBusRTU_Write_And_Read(int slave, int write_addr, int write_nb, const uint16_t *write_data, int read_addr, int read_nb, uint16_t *read_buf);



        std::string ModBusRTU_Test_Data_All();

        std::string ModBusRTU_Test_Data_L_1();

        std::string ModBusRTU_Test_Data_H_1();

        std::string ModBusRTU_Test_Data_H_2();




        uint16_t swapEndian_U16(uint16_t value);

        uint32_t swapEndian_U32(uint32_t value);

        template <std::size_t N>
        void swapEndian_U16(std::array<uint16_t, N>& arr)
        {
            for (std::size_t i = 0; i < N; ++i) 
            {
                arr[i] = ((arr[i] >> 8) & 0x00FF) |
                        ((arr[i] << 8) & 0xFF00);
            }
        }

        template <std::size_t N>
        void swapEndian_U32(std::array<uint32_t, N>& arr) 
        {
            for (auto& value : arr) 
            {
                value = ((value >> 24) & 0x000000FF) |
                        ((value >> 8)  & 0x0000FF00) |
                        ((value << 8)  & 0x00FF0000) |
                        ((value << 24) & 0xFF000000);
            }
        }




    // private:

        modbus_t *ctx;

        int ModBusBaud;

        const char *ModBusDevice;



        std::string ModBusTEST_ERROR = "";

        std::array<uint16_t, READNB>  Read_Data_All = {0};

        std::array<uint16_t, WRITENB> Write_Data_All  = {0};

        std::array<uint16_t, READNB_H_1>  Read_Data_H_1 = {0};

        std::array<uint16_t, WRITENB_H_1> Write_Data_H_1  = {0};

        std::array<uint16_t, READNB_H_2>  Read_Data_H_2 = {0};

        std::array<uint16_t, WRITENB_H_2> Write_Data_H_2  = {0};

        std::array<uint16_t, READNB_L_1>  Read_Data_L_1 = {0};

        std::array<uint16_t, WRITENB_L_1> Write_Data_L_1  = {0};


};

#endif

