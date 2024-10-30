#pragma once
#include <cstdint>

#include "Tank.h"

class Pump {
    private:
        float m_pumpPower;
        float m_volumeStream;   //cm³/s
        bool m_active;
        Tank &m_tank;
        Tank &m_neighbouringTank;
        std::uint16_t m_id;

        

    public: 
        Pump(float pumpPower,float volumeStream, bool active, Tank &tank, Tank &neighbouringTank, std::uint16_t id) 
        : m_pumpPower(pumpPower) , m_volumeStream(volumeStream), m_active(active), m_tank(tank), m_neighbouringTank(neighbouringTank), m_id(id){};


        ~Pump() = default;

        void startPump();
        void stopPump();

        void extractFluidFromTank();
        void fillNeighbouringTank();

        void amplifyVolumeStream();
        void reduceVolumeStream();

        bool isActive();

        float getVolumeStream();

};