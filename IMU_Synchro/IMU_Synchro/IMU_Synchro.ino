#include <M5StickC.h>
#include "BluetoothSerial.h"

BluetoothSerial bt;
const char *bt_name = "M5stickC";

int color1 = 0x0000; //通常時の色
int color2 = 0xFFFF; //同期時の色

/*
#define TFT_BLACK       0x0000      
#define TFT_NAVY        0x000F      
#define TFT_DARKGREEN   0x03E0      
#define TFT_DARKCYAN    0x03EF     
#define TFT_MAROON      0x7800      
#define TFT_PURPLE      0x780F      
#define TFT_OLIVE       0x7BE0      
#define TFT_LIGHTGREY   0xC618      
#define TFT_DARKGREY    0x7BEF      
#define TFT_BLUE        0x001F     
#define TFT_GREEN       0x07E0      
#define TFT_CYAN        0x07FF      
#define TFT_RED         0xF800      
#define TFT_MAGENTA     0xF81F      
#define TFT_YELLOW      0xFFE0     
#define TFT_WHITE       0xFFFF      
#define TFT_ORANGE      0xFDA0      
#define TFT_GREENYELLOW 0xB7E0     
#define TFT_PINK        0xFC9F
*/


float accX = 0.0F;
float accY = 0.0F;
float accZ = 0.0F;

float gyroX = 0.0F;
float gyroY = 0.0F;
float gyroZ = 0.0F;

float pitch = 0.0F;
float roll  = 0.0F;
float yaw   = 0.0F;

float pre = 0.0F;

float threshold = 3.0F; //域値

void setup() {
  Serial.begin(115200);
  bt.begin(bt_name);
  M5.begin();
  M5.IMU.Init();
  M5.Lcd.setRotation(0);
  M5.Lcd.fillScreen(color1);
}

void loop() {
  M5.IMU.getAccelData(&accX,&accY,&accZ);
  if (abs(accX-pre) > threshold){
    M5.Lcd.fillScreen(color2);
    delay(10000);
    M5.Lcd.fillScreen(color1);
  }
  pre = accX;
}
