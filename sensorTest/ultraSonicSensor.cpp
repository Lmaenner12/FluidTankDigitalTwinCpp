#include "ultraSonicSensor.h"

#include <inttypes.h>

uint32_t ultraSonicSensor::measureDistance(){

    digitalWrite(m_triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(m_triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(m_triggerPin, LOW);
    delayMicroseconds(2);

    m_duration = pulseIn(m_echoPin, HIGH, PULSE_TIMEOUT);
    m_currentDistance = MicrosecondsToCentimeter(m_duration);
    return m_currentDistance;
}


uint32_t ultraSonicSensor::calcDistanceAvg(){
    uint32_t minVal, maxVal, avg, currentVal;
    minVal = 999;
    maxVal = 0;
    avg = currentVal = 0;

    // Build the average of DEFAULT_PING_COUNT number of values.
    // Min and Max are removed from the count to reduce influence of Extrem Values and Measuring noise

    for (uint8_t x = 0; x < DEFAULT_PING_COUNT + 2; ++x) {
        currentVal = measureDistance();

        if(currentVal < minVal) {
            minVal = currentVal;
        }

        if(currentVal > maxVal) {
            maxVal = currentVal;
        }

        avg += currentVal;
    }

    avg -= (maxVal + minVal);

    return avg/DEFAULT_PING_COUNT;
}



uint32_t ultraSonicSensor::getDistance(){
    return m_distance;
}


uint32_t ultraSonicSensor::MicrosecondsToCentimeter(uint32_t duration) {
    // The sensor measures the duration of an trigger signal and its returning echo
    // So the Signal travels double the measured distance
    // For 1 meter the signal needs 2 * 1 / 340 m/s = 0.005883 s = 5.883 ms = 5883 µs
    // no decimal numbers are allowed for integers. Thats why we need microseconds to reduce rounding errors
    // other option: use double or float.
    uint32_t distance = (duration * 100) / 5882;

    return distance;
}
