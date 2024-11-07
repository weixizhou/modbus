
#include "main.hpp"


extern __global_variable__ *global_variable;


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
 * 
 ****/



// Platform-specific function to get current ticks (milliseconds)
uint32_t getPlatformTicks()
{
    struct timeval now;
    gettimeofday(&now, NULL);
    return now.tv_sec * 1000LL + now.tv_usec / 1000;
}





