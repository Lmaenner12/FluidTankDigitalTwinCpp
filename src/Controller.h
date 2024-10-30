#pragma once
#include <cstdint>

#include "Pump.h"
#include "Tank.h"
#include "Sensor.h"

class Controller 
{
    private:
    Tank &m_tank1;
    Tank &m_tank2;
    Tank &m_tank3;
    Tank &m_tank4;

    Pump &m_pump1;
    Pump &m_pump2;
    Pump &m_pump3;

    Sensor &m_sensor1;
    Sensor &m_sensor2;
    Sensor &m_sensor3;
    Sensor &m_sensor4;


    public:
    Controller( Tank &tank1,
                Tank &tank2,
                Tank &tank3,
                Tank &tank4,
                Pump &pump1,
                Pump &pump2,
                Pump &pump3,
                Sensor &sensor1,
                Sensor &sensor2,
                Sensor &sensor3,
                Sensor &sensor4) 
        : m_tank1(tank1), m_tank2(tank2), m_tank3(tank3), m_tank4(tank4), m_pump1(pump1), m_pump2(pump2), m_pump3(pump3), m_sensor1(sensor1), m_sensor2(sensor2), m_sensor3(sensor3), m_sensor4(sensor4){}

    ~Controller() = default;

    void mixtureFiftyPercent(float volume);
    void sourceTankExtraction(Pump &pump, Tank &tank, Sensor &sensor);
    void mixtureUserDefined(float volume , std::uint16_t portionTank1, std::uint16_t portionTank2);

    void continuousFillTank4();
    void simpleRegulation();

    void AdjustPumpStreamsBy20Percent();

    void adjustPumpStreams();
};