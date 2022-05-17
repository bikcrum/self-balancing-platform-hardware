#include "Wire.h"
#include <MPU6050_light.h>
#include <Servo.h>

Servo servoX;
Servo servoY;

MPU6050 mpu(Wire);
unsigned long timer = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  servoX.attach(10);
  servoY.attach(9);
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while (status != 0) { }
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000); \
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done!\n");
}

int offX = 87;
int offY = 87;

void loop() {
  mpu.update();
  
  if ((millis() - timer) > 10) {
    
    int angX = (int)mpu.getAngleX();
    int angY = (int)mpu.getAngleY();
    
    servoX.write(angX + offX);
    servoY.write(angY + offY);
    
    timer = millis();
  }
  
}
