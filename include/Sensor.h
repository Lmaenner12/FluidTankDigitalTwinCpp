#pragma once

#include "Tank.h"

class Sensor {
    private:
        float m_value;
        Tank &m_tank;

    public: 
        Sensor(Tank &tank) : m_value(tank.getFluidLevel()), m_tank(tank){};
        ~Sensor() = default;

    float getCurrentValue();
    void measureFluidLevel();
    void updateTankFluidLevel();
    
        
};