//  Code by Pedro Costa
//  09/2018
//
// Crabbie Robot Project
// MIT License
// Autonomous bio-inspired crab robot prototype which responds to changes in ambient light

#include <Servo.h>

#define TRUE  1
#define FALSE 0

// Sets the LED pin
#define LED_PIN 13
// Total used servos
#define ACTUATORS 4
// May need manual calibration depending on the environment!
#define DARK_THRESHOLD 512

typedef unsigned short ushort_t;

// Mode detection and runtime control variables
ushort_t dark;
dark = FALSE;

void attachServos (
    Servo group[],
    ushort_t pins[])
{
    for (int i = 0; i < ACTUATORS; i++) {
        group[i].attach(pins[i]);
    }
}

// Iterates over the difference between two degrees writing an updated magnitude on each servo
void writeServos (
    Servo group[], 
    int initialDof,
    int finalDof,
    int magnitude)
{
    for (int i = initialDof; i < finalDof; i += magnitude) {
        for (int j = 0; j < ACTUATORS; j++) {
            group[j].write(i);
        }
    }
}

int isDark (int sensorValue) {
    if (sensorValue < DARK_THRESHOLD)
        return TRUE;
    else
        return FALSE;
}

void blinkLed (
    int pin,
    int miliSecs)
{
    digitalWrite(pin, HIGH);
    delay(miliSecs);
    digitalWrite(pin, LOW);
    delay(miliSecs);
}

void setup()
{
    // LED indication
    pinMode(13, OUTPUT);

    Servo servo[4];
    int servoPins[4] = {4, 5, 6, 7};

    attachServos(servo, servoPins);

    Serial.begin(9600);
}

void loop()
{
    if (dark == FALSE) {
        writeServos(servo, 0, 180, 1);
        dark = isDark(analogRead(A0));
    } else {
        blinkLed(LED_PIN, 500);
        dark = isDark(analogRead(A0));
    }
}