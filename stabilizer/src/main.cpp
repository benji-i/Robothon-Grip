#include <Arduino.h>

// Most ESP32 dev boards have a built-in LED on pin 2
#define LED_PIN 2

void setup() {
    Serial.begin(115200);           // open serial connection to your laptop
    pinMode(LED_PIN, OUTPUT);       // tell the ESP32 this pin is an output
    Serial.println("Setup complete, starting blink...");
}

void loop() {
    digitalWrite(LED_PIN, HIGH);    // turn LED on
    Serial.println("LED ON");
    delay(1000);                    // wait 1 second

    digitalWrite(LED_PIN, LOW);     // turn LED off
    Serial.println("LED OFF");
    delay(1000);
}