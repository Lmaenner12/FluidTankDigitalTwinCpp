
#include "Tank.h"

void Tank::setFluidLevel(float val) {
    this->m_fluidLevel = val;
}

void Tank::setVolume(float val) {
    this->m_volume = val;
}

void Tank::refillTank() {
    if(this->m_fluidLevel > 100.0f) return;

    this->m_fluidLevel = 100.0f;
    ++m_refillCounter;
}

float Tank::getMinFluidLevel(){
    return this->m_minFluidLevel;
}

float Tank::getMaxFluidLevel(){
    return this->m_maxFluidLevel;
}

float Tank::getFluidLevel(){
    return this->m_fluidLevel;
}

float Tank::getVolume(){
    return this->m_volume;
}

bool Tank::isEmpty(){
    if(this->m_fluidLevel < 1.0f){
        return true;
    }

    return false;
}

bool Tank::canTankBeRefilled(){
    return this->m_canBeRefilled;
}

std::uint16_t Tank::getTankId()
{
    return this->m_tankId;
}
