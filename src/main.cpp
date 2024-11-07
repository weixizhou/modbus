#include "main.hpp"

/*
 * 这本工程用到了fmt--> sudo apt install libfmt-dev
 */


__global_variable__ _global_variable_, *global_variable = &_global_variable_;


int main(int argc, char *argv[])
{

    global_variable->modbuscontroller = new ModBusController("/dev/ttyUSB1", 1500000);

    uint32_t last_time = getPlatformTicks();

    while (true)
    {


        global_variable->modbuscontroller->modbustest->delta_data();


        // delta_data();

        // delta_data_h_1();

        // delta_data_h_2();

        // if (getPlatformTicks() - last_time > 3000)
        // {
            // delta_data_l_1();

        //     last_time = getPlatformTicks();
        // }
    }

    global_variable->modbuscontroller->~ModBusController();

    return 0;
}
