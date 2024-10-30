#pragma once

#include "Sensor.h"
#include "Pump.h"

void render();

void renderSensorPlot(const Sensor &sensor);

void renderMultipleSensorsPlot(const std::vector<Sensor>& sensors);

void renderSingleSensorPlot(const Sensor &sensor, int sensorId);

void renderPumpButton(Pump &pump, const char* label);

void renderRefillButton(Tank &tank, const char* label);

void renderPumpStatus(Pump &pump, const char* label);
