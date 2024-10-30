#include <iostream>

#include "Controller.h"
#include "Pump.h"
#include "Sensor.h"
#include "Tank.h"
#include "main.h"


int main() {

    //ToDO: Erstelle Array mit Objekten, um Konstruktor zu vereinfachen
    Tank tank_1 = Tank(100.0f , 5.0f, 50.0f,true,1 );
    Tank tank_2 = Tank(100.0f , 5.0f, 70.0f,true,2 );
    Tank tank_3 = Tank(10.0f , 5.0f, 2.0f,false,3 );
    Tank tank_4 = Tank(10.0f , 5.0f, 0.0f,false,4 );

    Pump pump_1 = Pump(50.0f, 50.0f / 60, 100.0f / 60, false, tank_1, tank_3,1);
    Pump pump_2 = Pump(50.0f, 50.0f / 60, 100.0f / 60, false, tank_2, tank_3,2);
    Pump pump_3 = Pump(50.0f, 50.0f / 60, 100.0f / 60, false, tank_3, tank_4,3);

    Sensor sensor_1 = Sensor(tank_1);
    Sensor sensor_2 = Sensor(tank_2);
    Sensor sensor_3 = Sensor(tank_3);
    Sensor sensor_4 = Sensor(tank_4);

    Controller controller = Controller(tank_1,tank_2,tank_3,tank_4,pump_1,pump_2,pump_3,sensor_1,sensor_2,sensor_3,sensor_4);

    std::cout << "50/50 Mixture Mode for 10 cm³ :\n";
    controller.mixtureFiftyPercent(10.0f);
    printFluidLevels(sensor_1, sensor_2, sensor_3, sensor_4);

    char cancel;

    std::cout << "Start Simulation of continous Flow? (y/n)";
    std::cin >> cancel;

    int whileCounter = 0;

    while(cancel == 'y')
    {


        controller.continuousFillTank4();

        if(whileCounter % 20 == 0) {
            printFluidLevels(sensor_1, sensor_2, sensor_3, sensor_4);
            std::cout << "Simulate further ? (y/n)";
            std::cin >> cancel;
        }
        ++whileCounter;
    }

    std::cout << "Start Simulation of simple regulation? (y/n)";
    std::cin >> cancel;

    int whileCounter2 = 0;

    while(cancel == 'y')
    {
        controller.simpleRegulation();

        if(whileCounter2 % 20 == 0) {
            printFluidLevels(sensor_1, sensor_2, sensor_3, sensor_4);
            std::cout << "Simulate further ? (y/n)";
            std::cin >> cancel;
        }

        ++whileCounter2;
    }

    return 0;
}

void printFluidLevels(Sensor &sensor_1, Sensor &sensor_2, Sensor &sensor_3, Sensor &sensor_4)
{
    std::cout << "\nFluid Level Tank 1: " << sensor_1.getCurrentValue() << "\n";
    std::cout << "Fluid Level Tank 2: " << sensor_2.getCurrentValue() << "\n";
    std::cout << "Fluid Level Tank 3: " << sensor_3.getCurrentValue() << "\n";
    std::cout << "Fluid Level Tank 4: " << sensor_4.getCurrentValue() << "\n";
    std::cout << "_____________________\n\n";
}
