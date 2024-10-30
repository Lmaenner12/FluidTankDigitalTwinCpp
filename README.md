# Fluid Tank Digital Twin
This is a C++ programm that simulates the connection of 4 fluid tanks using ImGui and ImPlot for rendering. The Tanks are connected via pumps and sensors are measuring the height of the fluid (Fluidlevel). The connection of the tanks looks as follows:

![Pump_Config](https://github.com/user-attachments/assets/c361d10c-4977-4991-8c01-059f86dbde9a)

**Goal**: Create a digital Twin, which simulates different controll states of the tanks and delivers optimal Parameters for a real controller of the tanks.

## Prerequisites

- CMake
- Qt
- C++20 or higher
- Microsoft Visual Studio 2022


### To Do´s
- Refactoring of the Code
- Implement controll states
- Fix the GUI, so that the Windows are located at fixed places and are not movable
- Create GUI for initial values of the tanks and pumps (e.g. power, volumestream)
- Enable a live connection to a real sensor

#### Controlls:
As of right now, the tanks have fixed initial values. You can press start or stop the pumps and a button to refill tank 1 or 2. The plots show the fluidlevel measured by the sensor of the respektive tanks.
