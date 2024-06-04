# Table of Contents

- [Embedded Systems Architecture Labs](#embedded-systems-architecture-labs)
- [Final Project - Monitoring System](#final-project---monitoring-system)
- [Team Members](#team-members)


---

# Embedded Systems Architecture Labs

This repository contains the files and source code for various labs in the Embedded Systems Architecture course.

## Labs Overview

| Lab Number | Main Source Code | Kit Video | Code & Simulation Video | Proteus Project | Hex File |
|------------|------------------|-----------|-------------------------|----------------|----------|
| Lab01      | [main.c](Lab01/src/main.c) | [Lab1.mp4](Lab01/vid/Lab1.mp4) | - | [Lab01.pdsprj](Lab01/Lab01.pdsprj) | [Lab01.hex](Lab01/Lab01.hex) |
| Lab02      | [main.c](Lab02/src/main.c) | [Lab2.mp4](Lab02/vid/Lab2.mp4) | - |[Lab02.pdsprj](Lab02/Lab02.pdsprj) | [Lab02.hex](Lab02/Lab02.hex) |
| Lab03      | [main.c](Lab03/src/main.c) | [Lab3_Kit.mp4](Lab03/vid/Lab03_Kit.mp4) | [Lab3_code&simulation.mp4](Lab03/vid/Lab03_codeAndSimulation.mp4) |[Lab03.pdsprj](Lab03/Lab03.pdsprj) | [Lab03.hex](Lab03/Lab03.hex) |
| Lab04      | [main_master.c](Lab04/master/main.c), [main_slave.c](Lab04/slave/main.c) | [Lab4_Kit.mp4](Lab04/vid/Lab04_Kit.mp4) | - |[Lab04.pdsprj](Lab04/Lab04.pdsprj) | - |
| Lab05      | [main_sender.c](Lab05/sender/main.c), [main_receiver.c](Lab05/receiver/main.c) | [Lab5_Kit.mp4](Lab05/vid/Lab05_Kit.mp4) | - |[Lab04.pdsprj](Lab05/Lab05.pdsprj) | [Lab05_sender.hex](Lab05/Lab05_sender.hex), [Lab05_reciever.hex](Lab05/Lab05_reciever.hex) |

# Final Project - Monitoring System

## Project Overview

This project focuses on creating an intuitive and user-friendly Embedded Monitoring System designed to enhance home security and comfort. The system allows users to monitor their home environment in real-time using various sensors and provides automated responses to critical events. The system prioritizes ease of use and seamless integration into daily routines.

## Project Idea

The Embedded Systems Monitoring System uses the following sensors to monitor house status:
- **Temperature Sensor**
- **LDR Sensor**
- **Soil Moisture Sensor**
- **Flame Sensor**
- **Gas Sensor**

An ESP32 module is used for WiFi connectivity, allowing users to access the house status remotely. In case of emergencies, the system can trigger a buzzer to alert users or activate a water bulb to extinguish fires.

## Objectives

1. **Real-Time Monitoring**: Enable users to monitor key environmental parameters such as temperature, light intensity, soil moisture, flame, and gas levels in real-time.
2. **User-Friendly Initialization**: Develop an intuitive initialization process for easy setup and network connection without requiring technical expertise.
3. **Automated Responses**: Implement automated response mechanisms for critical events like fire detection or gas leaks, ensuring timely alerts and appropriate actions.
4. **Seamless Integration**: Create a system that integrates seamlessly into daily life, providing continuous monitoring and alerts without disruption.
5. **Scalability**: Design the system to be scalable, allowing for future expansion and integration of additional sensors or functionalities.

## Stakeholders

- **Homeowners**: Primary users concerned with home security and comfort.
- **Family Members**: Residents benefiting from enhanced security.
- **Plants**: The system provides information about the plants in the house, impacting their health.
- **Manufacturers**: Suppliers of hardware and software components.

## Components

| Component              | Description                      |
|------------------------|----------------------------------|
| ATmega32 microcontroller | Microcontroller for processing tasks. |
| ESP32                  | WiFi module for connectivity.    |
| LDR Sensor             | Light-dependent resistor for light sensing. |
| DHT11 Sensor           | Temperature and humidity sensor. |
| Flame Sensor           | Sensor for detecting flames.     |
| Gas Sensor             | Sensor for detecting gas levels. |
| Soil Moisture Sensor   | Sensor for measuring soil moisture. |
| Buzzer                 | Audible alert component.         |
| Servo                  | Actuator for precise movement.   |


## Feasibility Study

### Economical

1. **Cost-Effective Microcontroller Alternatives**:
   - Consider alternatives like ATmega16 or ATmega8 to reduce costs.
2. **Affordability and Accessibility**:
   - Explore alternative microcontroller options to make the system more affordable.
3. **Examples of Cost Reduction for WiFi Module**:
   - Alternatives like the ESP8266 can be used instead of ESP32 for lower costs.

### Environmental Effects

#### Pros:
- Reduced energy consumption due to efficient microcontrollers and sensors.

#### Cons:
- Potential electronic waste and increased energy consumption if not optimized.

#### Sustainability Initiatives:
- Integrate renewable energy sources like solar power to reduce reliance on traditional energy sources.

## Estimated Hardware Requirements

1. **Microcontrollers**:
   - ATmega32 or alternatives
   - ESP32 or alternatives

2. **Sensors**:
   - Temperature, LDR, Soil Moisture, Flame, Gas

3. **Additional Components**:
   - Power supply, Alarm system, Actuators

4. **Interfacing Components**:
   - Resistors, capacitors, Breadboard/PCB

## Team Members
- Abdulrahman Mohsen
- Amr Hossam
- Mariam Ashraf
- Mina Malak
- Yaseen Ashraf
