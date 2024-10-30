#pragma once

#include <cmath>
#include <cstdint>

#include "AdConstants.h"

class Tank {
    private:
    float m_height;
    float m_radius;
    float m_volume;
    float m_fluidLevel;
    float m_minFluidLevel;
    float m_maxFluidLevel;
    std::uint32_t m_refillCounter;
    bool m_canBeRefilled;

    public: 
    Tank(float height, float radius, float fluidLevel, bool canBeRefilled) 
    : m_height(height) , m_radius(radius), m_volume(m_height* static_cast<float>(std::pow(m_radius,2))*PI) , m_fluidLevel(fluidLevel), m_minFluidLevel(2.0f), m_maxFluidLevel(15.0f), m_refillCounter(0), m_canBeRefilled(canBeRefilled){};

    ~Tank() = default;

    void setFluidLevel(float val);
    void setVolume(float val);
    void refillTank();

    float getFluidLevel();
    float getVolume();
    float getMinFluidLevel();
    float getMaxFluidLevel();

    bool isEmpty();
    bool canTankBeRefilled();

};