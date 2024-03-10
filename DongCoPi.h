#ifndef DONGCO_PI
#define DONGCO_PI

#define ppr 2900  // xung trên vòng
#define ppm 2000  // xung trên mét

#define vanToc 10
#define ppm 1000  // xung trên met

#define minTimer 700   //max speed
#define maxTimer 2000  //min speed

#define timeTangoc 3000  // >1000
#define soLantang 5      // (maxTimer-minTimer)/100
#define time1lantang timeTangoc / soLantang

#define PAUSE 0x00
#define RESUME 0x01
#define UP 0x02
#define DOWN 0x03
#define LEFT 0x04
#define RIGHT 0x05

#define STOP 0x10
#define UP_LATE 0x12
#define DOWN_LATE 0x13
#define LEFT_LATE 0x14
#define RIGHT_LATE 0x15

#define RO_LEFT 0x20
#define RO_RIGHT 0x21

#define START_BYTE 0x80
#define STOP_BYTE 0x81

#endif