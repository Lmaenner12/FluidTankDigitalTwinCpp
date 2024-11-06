#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <inttypes.h>
#include "AdConstants.h"

class ultraSonicSensor {
    private:
        uint32_t m_currentDistance;
        uint8_t m_echoPin, m_triggerPin;
        uint32_t m_duration, m_distance;
        bool m_autoMode;

        uint32_t MicrosecondsToCentimeter(uint32_t duration);

    public:
        ultraSonicSensor(uint8_t echoPin, uint8_t triggerPin)
        : m_currentDistance(0), m_echoPin(echoPin), m_triggerPin(triggerPin), m_duration(0), m_distance(0) {
            pinMode(m_echoPin, INPUT);
            pinMode(m_triggerPin, OUTPUT);
        }
        ~ultraSonicSensor() = default;

        uint32_t measureDistance();
        uint32_t calcDistanceAvg();
        uint32_t getDistance();

};
