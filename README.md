# Drink Dispenser Robot 🍹

A custom-built automated drink dispenser powered by **Arduino** and **ROS (Robot Operating System)**. Designed to detect a glass, lower it, pour a selected drink, and return the glass—fully hands-free and remote-controlled.

## 🚀 Project Overview

This drink dispenser combines **ROS** for high-level control and coordination with **Arduino** for low-level motor and sensor interactions. It uses object detection to ensure the dispensing sequence only starts when a glass is present, preventing messes or misfires.

### 🛠️ Features

- **Drink Detection System**  
  Infrared or ultrasonic sensor detects the presence of a glass before the sequence begins.

- **Motorized Glass Platform**  
  A motor lowers the glass until a **bottom-limit button** is triggered, ensuring accurate positioning.

- **Servo-Driven Dispensing Arm**  
  A servo motor rotates a dispensing arm with drink tubes to position over the glass.

- **Dual Water Pump System**  
  Two pumps provide a selection of drink options, activated once the arm is in position.

- **Automated Return**  
  After pouring, the arm returns to its original position and the platform lifts the glass until a **top-limit switch** is triggered.

- **Remote Control Interface**  
  Start and control the sequence remotely for a hands-free user experience.

---

## ⚙️ System Architecture

```plaintext
[Remote]
   |
   v
[ROS Master] --- [Arduino Mega]
       |               |
       |          [Motors / Servos / Sensors]
       |
   [Sequence Logic]
