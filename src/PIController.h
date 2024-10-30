#pragma once

#include "Tank.h"
#include "Pump.h"

class PIController {
    private:
        float m_kp; // Proportionalfaktor
        float m_ki; // Integralfaktor
        float m_setpoint; // Sollwert für den Füllstand
        float m_integral; // Integraler Fehleranteil
        float m_lastError; // Letzter Fehlerwert für den Fehlervergleich

    public:
        PIController(float kp, float ki, float setpoint)
            : m_kp(kp), m_ki(ki), m_setpoint(setpoint), m_integral(0.0f), m_lastError(0.0f) {}

        float update(float &currentLevel);

        void controlPumpForTank4(Tank &tank4, Pump &pump3);

        void setSetpoint(float setpoint);

};
