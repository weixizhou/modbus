

#define MODBUS_BAUD    1500000
#define MODBUS_DEVICE  "/dev/ttyUSB1"

// 一次性数据收发调试
#define SLAVE           0x8F
#define READNB          100
#define READADDR        0x00
#define WRITENB         58
#define WRITEADDR       0x01


// 分频调试
#define SLAVE_HL        0x8E

// 数据读取
// 高频1
#define READNB_H_1      76
#define READADDR_H_1    0x01

// 高频2
#define READNB_H_2      14
#define READADDR_H_2    0x02

// 低频
#define READNB_L_1      12
#define READADDR_L_1    0x03


// 数据发送
// 高频1
#define WRITENB_H_1     58
#define WRITEADDR_H_1   0x11

// 高频2
#define WRITENB_H_2     10
#define WRITEADDR_H_2   0x12

// 高频3
#define WRITENB_L_1     10
#define WRITEADDR_L_1   0x13




#define TEST_REG_
#define TEST_DEBUG_
#define MODBUS_FPS


#ifdef MODBUS_FPS
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
#else
    #define _CALC_FPS(tips)
#endif



struct IMUData 
{
    float acc_x;
    float acc_y;
    float acc_z;
    float gyro_x;
    float gyro_y;
    float gyro_z;
    float angle_x;
    float angle_y;
    float angle_z;
};


struct LedData 
{
    // RGB




    uint16_t led_mode;

};


struct EspSystemStatus
{
    
};


struct BatteryData 
{
    uint16_t volt;
    uint16_t current;
    uint16_t avg_current;
    uint16_t temperature;
    uint16_t run_time_to_empty;
    uint16_t avg_run_time_to_empty;
    uint16_t avg_charge_time_to_full;
    uint16_t remaing_capacity;
    uint16_t remaining_power_percentage;
};


static const uint16_t maxJoy = 0xffff;
static const uint16_t maxTrig = 0x3ff;
struct GamepadData
{
  uint16_t joy_LHori = maxJoy / 2;
  uint16_t joy_LVert = maxJoy / 2;
  uint16_t joy_RHori = maxJoy / 2;
  uint16_t joy_RVert = maxJoy / 2;

  uint16_t trig_LT, trig_RT;

  bool btn_A, btn_B, btn_X, btn_Y;
  bool btn_DirUp, btn_DirLeft, btn_DirRight, btn_DirDown;
  
  bool btn_LB, btn_RB;
  bool btn_LS, btn_RS;
  bool btn_Share, btn_Start, btn_Select, btn_Xbox;
};

