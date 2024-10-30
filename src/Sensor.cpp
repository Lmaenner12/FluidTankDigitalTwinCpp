

#include "Sensor.h"
#include "Tank.h"

void Sensor::measureFluidLevel() {
    // ToDo: Connect MQTT Broker Sensor Value to member variable m_value
    this->m_value = this->m_tank.getFluidLevel();
    this->updateTankFluidLevel();
}

void Sensor::updateTankFluidLevel(){
    this->m_tank.setFluidLevel(this->m_value);
};


float Sensor::getCurrentValue(){
    this->measureFluidLevel();
    m_measuredFluidLevels.push_back(m_value);
    m_timeStamps.push_back(m_currentTime);
    m_currentTime += 0.1;
    return m_value;
}

