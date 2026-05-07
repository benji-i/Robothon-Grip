#include <Arduino.h>
#include <Wire.h>
#include <MPU6050.h>
#include <ESP32Servo.h>

MPU6050 imu;
Servo servo_x;
Servo servo_y;

float angle_x = 0.0;
float angle_y = 0.0;
unsigned long last_time = 0;

#define NEUTRAL 90
#define GAIN    1.0

void setup() {
    Serial.begin(115200);
    Wire.begin();
    imu.initialize();

    servo_x.attach(13);
    // servo_y.attach(19);
    servo_x.write(NEUTRAL);
    // servo_y.write(NEUTRAL);

    last_time = millis();   // initialize before loop starts
}

void loop() {
    int16_t raw_ax, raw_ay, raw_az, raw_gx, raw_gy, raw_gz;
    imu.getMotion6(&raw_ax, &raw_ay, &raw_az, &raw_gx, &raw_gy, &raw_gz);

    float ax = raw_ax / 16384.0; Serial.print("AX: "); Serial.println(ax);
    float ay = raw_ay / 16384.0; Serial.print("AY: "); Serial.println(ay);
    float az = raw_az / 16384.0; Serial.print("AZ: "); Serial.println(az);
    float gx = raw_gx / 131.0; Serial.print("GX: "); Serial.println(gx);
    float gy = raw_gy / 131.0; Serial.print("GY: "); Serial.println(gy);

    unsigned long now = millis();
    float dt = (now - last_time) / 1000.0;
    last_time = now;

    float accel_angle_x = atan2(ay, az) * 180.0 / PI;
    float accel_angle_y = atan2(ax, az) * 180.0 / PI;

    float gyro_angle_x = angle_x + gx * dt;
    float gyro_angle_y = angle_y + gy * dt;

    angle_x = 0.96 * gyro_angle_x + 0.04 * accel_angle_x;
    angle_y = 0.96 * gyro_angle_y + 0.04 * accel_angle_y;

    int correction_x = constrain(NEUTRAL - (int)(angle_x * GAIN), 0, 180);
    int correction_y = constrain(NEUTRAL - (int)(angle_y * GAIN), 0, 180);

    servo_x.write(correction_x);
    // servo_y.write(correction_y);

    /**
    
    Serial.print("X: "); Serial.print(angle_x);
    Serial.print("  Y: "); Serial.print(angle_y);
    Serial.print("  Servo X: "); Serial.print(correction_x);
    Serial.print("  Servo Y: "); Serial.println(correction_y);

    */
    delay(10);  // run at roughly 100Hz
}