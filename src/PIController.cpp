
#include "Tank.h"
#include "Pump.h"
#include "PIController.h"

float PIController::update(float &currentLevel) {
    // Berechne den Fehler
    float error = m_setpoint - currentLevel;

    // Aktualisiere den Integrator
    m_integral += error * DELTA_TIME;

    // Berechne die Steuergröße u(t)
    float controlValue = m_kp * error + m_ki * m_integral;

    // Rückgabe der Steuergröße zur Anpassung der Pumpenleistung
    return controlValue;
}

void PIController::controlPumpForTank4(Tank &tank4, Pump &pump3) {
    float currentLevel = tank4.getFluidLevel();

    // Berechne die Pumpenleistung mit dem PI-Regler
    float controlValue = this->update(currentLevel);

    // Setze die Pumpenleistung abhängig vom Reglerausgang
    pump3.amplifyVolumeStream(controlValue);

    // Starte oder stoppe die Pumpe basierend auf dem Kontrollwert
    if (controlValue > 0) {
        pump3.startPump();
    } else {
        pump3.stopPump();
    }
}

void PIController::setSetpoint(float setpoint) { m_setpoint = setpoint; }
