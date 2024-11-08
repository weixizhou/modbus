#include "main.hpp"

/*
 * 这本工程用到了fmt--> sudo apt install libfmt-dev
 */


__global_variable__ _global_variable_, *global_variable = &_global_variable_;


int main(int argc, char *argv[])
{

    global_variable->modbuscontroller = new ModBusController(MODBUS_DEVICE, MODBUS_BAUD);

    while (true)
    {

        // fmt::printf(global_variable->modbuscontroller->modbustest->delta_data_all());

        // fmt::printf(global_variable->modbuscontroller->modbustest->delta_data_h_1());

        fmt::printf(global_variable->modbuscontroller->modbustest->delta_data_h_2());

        // fmt::printf(global_variable->modbuscontroller->modbustest->delta_data_l_1());

        // fmt::printf(global_variable->modbuscontroller->modbustest->delta_data_l_1());

    }

    global_variable->modbuscontroller->~ModBusController();

    return 0;
}
