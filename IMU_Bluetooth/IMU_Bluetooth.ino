#include <M5StickC.h>
#include "BluetoothSerial.h"

BluetoothSerial bt;
const char *bt_name = "M5stickC";


float accX = 0.0F;
float accY = 0.0F;
float accZ = 0.0F;

float gyroX = 0.0F;
float gyroY = 0.0F;
float gyroZ = 0.0F;

float pitch = 0.0F;
float roll  = 0.0F;
float yaw   = 0.0F;

boolean state = false;

void setup() {
  Serial.begin(115200);
  bt.begin(bt_name);
  M5.begin();
  M5.IMU.Init();
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setCursor(40,40);
  M5.Lcd.println("OFF");
  
}

void loop() {
  M5.update();
  if(M5.BtnA.wasPressed()){
    state = !state;
    M5.Lcd.setCursor(40,40);
    if(state == true) {
      M5.Lcd.println("ON");
      bt.println("start");
    }
    else {
      M5.Lcd.println("OFF");
      bt.println("end");
    }
    delay(100);
  }
  if (state == true){
      M5.IMU.getGyroData(&gyroX,&gyroY,&gyroZ);
      M5.IMU.getAccelData(&accX,&accY,&accZ);
      M5.IMU.getAhrsData(&pitch,&roll,&yaw);
      bt.printf("%5.2f %5.2f %5.2f\n", gyroX, gyroY, gyroZ);
      bt.printf("%5.2f %5.2f %5.2f\n", accX, accY, accZ);
      bt.printf("%5.2f %5.2f %5.2f\n", pitch, roll, yaw);

      
    /*bt.printf("GyroX GyroY GyroZ: %6.2f  %6.2f  %6.2f\n", gyroX, gyroY, gyroZ);
      bt.printf("accX, accY, accZ: %5.2f   %5.2f   %5.2f\n", accX, accY, accZ);
      bt.printf("Pitch Roll Yaw: %5.2f   %5.2f   %5.2f\n", pitch, roll, yaw);
      */
      delay(100);
  }
 
}
