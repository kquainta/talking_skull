#include <Arduino.h>
#include <Servo.h>

// Arduino Nano pin mapping
// Servos should be on PWM-capable pins (e.g. 9, 10, 11)
const int servoPin1 = 9;
const int servoPin2 = 10; // currently unused
const int servoPin3 = 11; // currently unused
// On-board LED (also works with external LED on pin 13)
const int ledPin = 13;

Servo servo1;
Servo servo2;
Servo servo3;

// Analog sensor pins on Nano (A0..A7)
const int analogPin1 = A1;
const int analogPin2 = A2;
const int analogPin3 = A3;

// Thresholds (scaled for 10-bit ADC on AVR Nano)
const int THRESHOLD1 = 100;
const int THRESHOLD2 = 75;
const int THRESHOLD3 = 13;

// Audio step values used to drive the jaw servo
const int AUDIO_STEP_SMALL = 40;
const int AUDIO_STEP_MEDIUM = 60; // currently unused
const int AUDIO_STEP_LARGE = 120;

void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);

  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);

  // LED indicates servo movement
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  int audioValue = 0;

  int analogValue1 = analogRead(analogPin1);
  int analogValue2 = analogRead(analogPin2);
  int analogValue3 = analogRead(analogPin3);

    // Determine audio level based on thresholds
  if (analogValue1 < THRESHOLD1) audioValue += AUDIO_STEP_SMALL;
  if (analogValue2 < THRESHOLD2) audioValue += AUDIO_STEP_MEDIUM;
  if (analogValue3 < THRESHOLD3) audioValue += AUDIO_STEP_LARGE;

  Serial.print("AnalogValue1: ");
  Serial.print(analogValue1);

  Serial.print(" | AnalogValue2: ");
  Serial.print(analogValue2);

  Serial.print(" | AnalogValue3: ");
  Serial.print(analogValue3);

  Serial.print(" | Audio: ");
  Serial.println(audioValue);

  // Write jaw value
  // Turn LED on while servo is driven (audioValue > 0)
  if (audioValue > 0) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  servo1.write(audioValue);
  if (audioValue == 45) delay(60);
  if (audioValue == 90) delay(120);
  if (audioValue == 180) delay(320);

  servo1.write(0);
  // servo returned to rest; turn LED off
  digitalWrite(ledPin, LOW);
  delay(200);
}
