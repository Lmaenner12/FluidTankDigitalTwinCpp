

#include "Controller.h"

void Controller::mixtureFiftyPercent(const float volume)
{

    float extractedVolumeTank1 = 0.0f;
    m_pump1.startPump();

    // Volume Mixture is supposed to be of equal parts. Thats why the volume is divided by NUM_OF_SOURCE_TANKS

    while(extractedVolumeTank1 < volume/NUM_OF_SOURCE_TANKS) {
        sourceTankExtraction(m_pump1, m_tank1, m_sensor1);
        extractedVolumeTank1 += m_pump1.getVolumeStream() * DELTA_TIME;
    }
    m_pump1.stopPump();


    float extractedVolumeTank2 = 0.0f;
    this->m_pump2.startPump();

    // Volume Mixture is supposed to be of equal parts. Thats why the volume is divided by NUM_OF_SOURCE_TANKS
    while(extractedVolumeTank2 < volume/NUM_OF_SOURCE_TANKS) {
        sourceTankExtraction(m_pump2, m_tank2, m_sensor2);
        extractedVolumeTank2 += m_pump2.getVolumeStream() * DELTA_TIME;
    }
    this->m_pump2.stopPump();



    this->m_pump3.startPump();
    float extractedVolumeTank3 = extractedVolumeTank1 + extractedVolumeTank2;

    while(extractedVolumeTank3 > 0)
    {
        m_pump3.extractFluidFromTank();
        m_pump3.fillNeighbouringTank();
        extractedVolumeTank3 -= m_pump3.getVolumeStream() * DELTA_TIME;
    }
    this->m_pump3.stopPump();
}

//ToDo: Rename Funktion for better understanding to TankExtraction, bc it is viable for all sorts of tanks
void Controller::sourceTankExtraction(Pump &pump, Tank &tank, Sensor &sensor)
{
    //if(sensor.getCurrentValue() < tank.getMinFluidLevel() && tank.canTankBeRefilled()) tank.refillTank();

    if(!pump.isActive()) return;

    pump.extractFluidFromTank();
    pump.fillNeighbouringTank();

}

void Controller::continuousFillTank4()
{
    m_pump1.startPump();
    m_pump2.startPump();
    m_pump3.startPump();

    AdjustPumpStreamsBy20Percent();
    sourceTankExtraction(m_pump1, m_tank1, m_sensor1);
    sourceTankExtraction(m_pump2, m_tank2, m_sensor2);
    sourceTankExtraction(m_pump3, m_tank3, m_sensor3);

}


void Controller::AdjustPumpStreamsBy20Percent()
{
    return;
};

void Controller::simpleRegulation()
{
    m_sensor1.getCurrentValue();
    m_sensor2.getCurrentValue();
    m_sensor3.getCurrentValue();

    //Annahme: Tank 1 und Tank 2 können beliebig nachgefüllt werden. Daher muss min/max von Tank 1 und 2 nicht überprüft werden
    if (m_sensor3.getCurrentValue() >= m_tank3.getMinFluidLevel())
    {
        m_pump1.startPump();
        m_pump2.startPump();
        m_pump3.startPump();
    }

    if(m_sensor1.getCurrentValue() > m_tank1.getMinFluidLevel()) m_pump1.startPump();
    if(m_sensor2.getCurrentValue() > m_tank2.getMinFluidLevel()) m_pump2.startPump();

    if(m_sensor3.getCurrentValue() < m_tank3.getMinFluidLevel())
    {
        m_pump3.stopPump();
    }

    if(m_sensor3.getCurrentValue() > m_tank3.getMaxFluidLevel())
    {
        m_pump1.stopPump();
        m_pump2.stopPump();
        m_pump3.startPump();
    }

    sourceTankExtraction(m_pump1, m_tank1, m_sensor1);
    sourceTankExtraction(m_pump2, m_tank2, m_sensor2);
    sourceTankExtraction(m_pump3, m_tank3, m_sensor3);
}
