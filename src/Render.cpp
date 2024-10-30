#include <cstdint>
#include <string>

#include "imgui.h"
#include "implot.h"

#include "RenderConstants.hpp"
#include "Render.hpp"
#include "Controller.h"
#include "PIController.h"
#include "Pump.h"
#include "Sensor.h"
#include "Tank.h"
#include "main.h"

void render()
{
    ImGui::SetNextWindowPos(ImVec2(0.0F, 0.0F));
    ImGui::SetNextWindowSize(ImVec2(WINDOWS_WIDTH, LANE_PLOT_TOTAL_HEIGHT));

    static Tank tank_1 = Tank(100.0f , 5.0f, 50.0f,true,1 );
    static Tank tank_2 = Tank(100.0f , 5.0f, 70.0f,true,2 );
    static Tank tank_3 = Tank(10.0f , 5.0f, 2.0f,false,3 );
    static Tank tank_4 = Tank(10.0f , 5.0f, 0.0f,false,4 );

    static Pump pump_1 = Pump(50.0f, 50.0f / 60, 100.0f / 60 ,false, tank_1, tank_3,1);
    static Pump pump_2 = Pump(50.0f, 50.0f / 60, 100.0f / 60 , false, tank_2, tank_3,2);
    static Pump pump_3 = Pump(50.0f, 50.0f / 60, 100.0f / 60 , false, tank_3, tank_4,3);

    static Sensor sensor_1 = Sensor(tank_1);
    static Sensor sensor_2 = Sensor(tank_2);
    static Sensor sensor_3 = Sensor(tank_3);
    static Sensor sensor_4 = Sensor(tank_4);


    static Controller controller = Controller(tank_1,tank_2,tank_3,tank_4,pump_1,pump_2,pump_3,sensor_1,sensor_2,sensor_3,sensor_4);
    static PIController picont = PIController(1.2f, 1.2f, 20);

    //controller.continuousFillTank4();

    //controller.simpleRegulation();

    picont.controlPumpForTank4(tank_4, pump_3);

    sensor_1.getCurrentValue();
    sensor_2.getCurrentValue();
    sensor_3.getCurrentValue();
    sensor_4.getCurrentValue();





    std::vector<Sensor> sensors = {sensor_1,sensor_2,sensor_3,sensor_4};

    if (ImGui::Begin("MainWindow", nullptr, WINDOW_FLAGS_CLEAN))
    {
        ImPlot::CreateContext();
        renderPumpButton(pump_1, "Pump 1 Status: %s");
        renderRefillButton(tank_1, "Pump 1 Status: %s");


        renderPumpButton(pump_2, "Pump 2 Status: %s");
        renderRefillButton(tank_2, "Pump 2 Status: %s");


        renderPumpButton(pump_3, "Pump 3 Status: %s");



        pump_1.extractFluidFromTank();
        pump_1.fillNeighbouringTank();

        pump_2.extractFluidFromTank();
        pump_2.fillNeighbouringTank();

        pump_3.extractFluidFromTank();
        pump_3.fillNeighbouringTank();



        renderSingleSensorPlot(sensor_1, 1);
        renderSingleSensorPlot(sensor_2, 2);
        renderSingleSensorPlot(sensor_3, 3);
        renderSingleSensorPlot(sensor_4, 4);
        ImGui::End();
    }
}

void renderSensorPlot(const Sensor &sensor) {

    if (ImGui::Begin("Fluid Level Plot")) { // Neues ImGui-Fenster öffnen
        if (ImPlot::BeginPlot("Fluid Level over Time")) { // Neuer ImPlot-Plot
            ImPlot::SetupAxes("Time (s)", "Fluid Level (L)", ImPlotAxisFlags_AutoFit, ImPlotAxisFlags_AutoFit);

            // Den Vektor `fluidLevels` mit `timeStamps` anzeigen
            ImPlot::PlotLine("Fluid Level", sensor.m_timeStamps.data(), sensor.m_measuredFluidLevels.data(), sensor.m_measuredFluidLevels.size());

            ImPlot::EndPlot();
        }
        ImGui::End();
    }

}

void renderMultipleSensorsPlot(const std::vector<Sensor>& sensors) {
    if (ImGui::Begin("Fluid Level Plot")) {
        if (ImPlot::BeginPlot("Fluid Levels Over Time")) {
            ImPlot::SetupAxes("Time (s)", "Fluid Level (L)", ImPlotAxisFlags_AutoFit, ImPlotAxisFlags_AutoFit);

            // Schleife über alle Sensoren, um für jeden Sensor eine Linie zu zeichnen
            for (size_t i = 0; i < sensors.size(); ++i) {
                const Sensor& sensor = sensors[i];

                // Erzeuge einen eindeutigen Namen für jede Linie basierend auf dem Sensor-Index
                std::string label = "Sensor " + std::to_string(i + 1);

                // Zeichne die Linie mit den Zeitstempeln und Fluidlevel-Werten des jeweiligen Sensors
                ImPlot::PlotLine("Fluid Level", sensor.m_timeStamps.data(), sensor.m_measuredFluidLevels.data(), sensor.m_measuredFluidLevels.size());
            }

            ImPlot::EndPlot();
        }
        ImGui::End();
    }
}

void renderSingleSensorPlot(const Sensor &sensor, int sensorId) {
    // Fenster für den jeweiligen Sensor erstellen
    std::string windowTitle = "Fluid Level Plot - Sensor " + std::to_string(sensorId);
    if (ImGui::Begin(windowTitle.c_str())) {
        if (ImPlot::BeginPlot(("Fluid Level of Sensor " + std::to_string(sensorId)).c_str())) {
            ImPlot::SetupAxes("Time (s)", "Fluid Level (L)", ImPlotAxisFlags_AutoFit, ImPlotAxisFlags_AutoFit);

            // Plotten der Daten des jeweiligen Sensors
            ImPlot::PlotLine("Fluid Level", sensor.m_timeStamps.data(), sensor.m_measuredFluidLevels.data(), sensor.m_measuredFluidLevels.size());

            ImPlot::EndPlot();
        }
        ImGui::End();
    }
}

void renderPumpButton(Pump &pump, const char* label ) {
    if (ImGui::Begin(label)) {
        // Button für Pumpe 1
        renderPumpStatus(pump, label);
        std::string label_inactive = "Stop Pump " + std::to_string(pump.getPumpId());
        std::string label_active = "Start Pump " + std::to_string(pump.getPumpId());



        if (ImGui::Button((!pump.isActive() ? label_active.c_str() : label_inactive.c_str() ))) {
            if (pump.isActive()) {
                pump.stopPump();
            } else {
                pump.startPump();

            }
        }

        ImGui::SameLine();

        ImGui::End();
    }
}

void renderRefillButton(Tank &tank, const char* label) {
    if (ImGui::Begin(label)) {
        // Button für Pumpe 1

        std::string label2 = "Refill Tank " + std::to_string(tank.getTankId());

        if (ImGui::Button(label2.c_str())) {
            tank.refillTank();
        }
        ImGui::End();
    }
}

void renderPumpStatus(Pump &pump, const char* label) {
    // Fenster für den Pumpenstatus öffnen
    if (ImGui::Begin(label)) {
        // Erstellen einer Farbe je nach Pumpenstatus

        bool pumpStatus = pump.isActive();
        ImU32 color = pumpStatus ? IM_COL32(0, 255, 0, 255) : IM_COL32(255, 0, 0, 255); // Grün für aktiv, Rot für inaktiv

        // Zeichnet einen gefüllten Kreis als Statusindikator
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        ImVec2 p = ImGui::GetCursorScreenPos();
        float radius = 10.0f; // Radius des Kreises
        draw_list->AddCircleFilled(ImVec2(p.x + radius, p.y + radius), radius, color);

        // Abstand nach dem Kreis
        ImGui::Dummy(ImVec2(radius * 2, radius * 2));

        // Beschriftung für die Pumpe hinzufügen
        ImGui::Text(label, pumpStatus ? "Running" : "Stopped");
        ImGui::End();
    }
}
