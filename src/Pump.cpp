#include <iostream>

#include "Pump.h"


void Pump::startPump() {

    this->m_active = true;

    std::cout << "Pump " << this->m_id << " active\n";
}

void Pump::extractFluidFromTank()
{
    if(!this->isActive()) return;

    if(this->m_tank.isEmpty())
    {
       this->stopPump();
       return;
    }

    auto currentFluidLevel = this->m_tank.getFluidLevel();
    float newFluidLevel = {};

    if(currentFluidLevel > 0.0f){
    //ToDo: Grundfläche ist hardcodiert, Klasse tank eine membervariable Fläche zuordnen
        newFluidLevel =
            currentFluidLevel - ((this->m_volumeStream * DELTA_TIME) / static_cast<float>(std::pow(5.0f, 2)) * PI);
    }

    if(newFluidLevel < 0){
        newFluidLevel = 0;
        this->stopPump();
    }
    this->m_tank.setFluidLevel(newFluidLevel);
}

void Pump::stopPump() {

    this->m_active = false;
}

void Pump::fillNeighbouringTank(){
    if(!this->isActive()) return;
    auto currentFluidLevel = this->m_neighbouringTank.getFluidLevel();
    //ToDo: Grundfläche ist hardcodiert, Klasse tank eine membervariable Fläche zuordnen
    auto newFluidLevel = currentFluidLevel + ((this->m_volumeStream * DELTA_TIME) / static_cast<float>(std::pow(5.0f,2))*PI);

    this->m_neighbouringTank.setFluidLevel(newFluidLevel);
}

void Pump::amplifyVolumeStream(float val)
{
    float newVolumeStream = this->m_volumeStream *= val;

    if(newVolumeStream <= m_maxVolumeStream) {
        this->m_volumeStream = newVolumeStream;
    }else
    {
        this->m_volumeStream = m_maxVolumeStream;
    }

};

void Pump::reduceVolumeStream()
{
    this->m_volumeStream /= 1.20f;
};

bool Pump::isActive()
{
    return m_active;
};

float Pump::getVolumeStream()
{
    return m_volumeStream;
};

std::uint16_t Pump::getPumpId()
{
    return this->m_id;
}
