//www.elegoo.com
//2016.12.08
#include "ultraSonicSensor.h"
#include <inttypes.h>

uint8_t TRIG_PIN = 12;
uint8_t ECHO_PIN = 11;
ultraSonicSensor sr04 = ultraSonicSensor(ECHO_PIN,TRIG_PIN);
uint32_t distance;

void setup() {
   Serial.begin(9600);
   delay(1000);
}

void loop() {
   distance=sr04.measureDistance();
   Serial.print(distance);
   Serial.println("cm");
   delay(1000);
}
