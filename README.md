# AJ-ORBIT Autonomous Line Tracking Robot

<p align="center">
  <img src="https://github.com/user-attachments/assets/24b7d585-2401-44a4-8ae9-523bb19570dd" alt="AJ-ORBIT Logo" width="160" style="border-radius: 50%;">
</p>

<p align="center">
  <strong>Autonomous Differential-Drive Line Tracking Robot</strong><br>
  <em>Engineered under the AJ-ORBIT Robotics & Hardware Initiative</em>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Platform-Arduino%20Uno%20R3-00979D?style=for-the-badge&logo=arduino&logoColor=white" alt="Platform">
  <img src="https://img.shields.io/badge/Architecture-Differential%20Drive-E10600?style=for-the-badge" alt="Architecture">
  <img src="https://img.shields.io/badge/Driver-L298N%20Dual%20H--Bridge-red?style=for-the-badge" alt="Driver">
  <img src="https://img.shields.io/badge/Sensors-Dual%20Optical%20IR-000000?style=for-the-badge" alt="Sensors">
</p>

---

## 📌 Project Overview

The **AJ-ORBIT Line Tracking Robot** is an autonomous mobile robot (AMR) prototype designed for automated track navigation, industrial automated guided vehicle (AGV) simulation, and low-latency feedback control.

Built on an **Arduino Uno R3** compute core coupled with an **L298N dual H-bridge motor controller**, the robot uses a forward-mounted differential infrared (IR) sensor array to detect contrast differences between the navigation track (black tape) and the floor plane (light reflective surface). 

The onboard system performs continuous closed-loop state evaluation, applying corrective differential torque to the left and right drive wheels to keep the vehicle locked along its intended trajectory.

---

## ⚙️ Working Principle & System Architecture

```text
       +---------------------------------------------+
       |             Floor Surface Track             |
       +---------------------------------------------+
                              |
                     [Optical Reflection]
                              v
       +----------------------+----------------------+
       |   Left IR Sensor     |   Right IR Sensor    |
       +----------------------+----------------------+
                              |
                     [Digital TTL Signals]
                              v
       +---------------------------------------------+
       |             Arduino Uno R3                  |
       |      - Trajectory Decision Logic            |
       |      - Dual PWM Differential Profiling      |
       +---------------------------------------------+
                              |
                     [Direction & PWM Duty]
                              v
       +---------------------------------------------+
       |         L298N Dual H-Bridge Driver          |
       +---------------------------------------------+
                 /                         \
         [Channel A]                     [Channel B]
               v                               v
    +--------------------+           +--------------------+
    | Left TT Gear Motor |           | Right TT Gear Motor|
    +--------------------+           +--------------------+
