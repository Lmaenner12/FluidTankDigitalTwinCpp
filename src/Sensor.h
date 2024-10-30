#pragma once

#include <vector>

#include "Tank.h"


class Sensor {
    private:
        float m_value;
        Tank &m_tank;



    public:
        std::vector<float> m_measuredFluidLevels;
        std::vector<float> m_timeStamps;
        float m_currentTime;

        Sensor(Tank &tank)
        : m_value(tank.getFluidLevel()), m_tank(tank), m_measuredFluidLevels(std::vector<float>{0.0f}), m_timeStamps(std::vector<float>{0.0f}), m_currentTime(0){};
        ~Sensor() = default;

    float getCurrentValue();
    void measureFluidLevel();
    void updateTankFluidLevel();



};
