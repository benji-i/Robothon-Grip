#include <MPU6050.h>
#include <ESP32Servo.h>

MPU6050 imu;
Servo stabilizer_x;

void setup() {
    Serial.begin(115200); // open a window to print debug info to laptop
    imu.begin(); // intialize the sensor
    stabilizer_x.attach(18); // attach servo to pin 18
}

void loop() {
    // obatin correction data
    float accel_x = imu.getAccelerationX();
    float accel_y = imu.getAccelerationY();
    float accel_z = imu.getAccelerationZ();

    // Calculate a correction angle
    float correction_x = calculateCorrection(accel_x);

    // Command the servo to counter it
    stabilizer_x.write(90 + correction_x); // 90 = neutral position
}