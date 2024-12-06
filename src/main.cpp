#include "main.hpp"

/*
 * 这本工程用到了fmt--> sudo apt install libfmt-dev
 */


__global_variable__ _global_variable_, *global_variable = &_global_variable_;


int main(int argc, char *argv[])
{

    ModBusRTUController ModBusRTUController;

    ModBusRTUController.ModBusRTU_Setup(MODBUS_DEVICE, MODBUS_BAUD);

    while (true)
    {

        fmt::printf(ModBusRTUController.ModBusRTU_Test_Data_All());

        // fmt::printf(ModBusRTUController->modbustest->ModBusRTU_Test_Data_H_1());

        // fmt::printf(ModBusRTUController->modbustest->ModBusRTU_Test_Data_H_2());

        // fmt::printf(ModBusRTUController->modbustest->ModBusRTU_Test_Data_L_1());

    }

    ModBusRTUController.ModBusRTU_Exit();

    return 0;
}
