# 🔒 Door Locker Security System

## 📌 Overview
This project implements a Door Locker Security System using two ATmega32 microcontrollers. The system allows users to unlock a door using a password while ensuring security through a multi-layered architecture.

## 🎯 System Features
- **Two Microcontrollers (ATmega32 @ 8MHz)**
  - `HMI_ECU`: Handles user interactions via LCD and Keypad.
  - `Control_ECU`: Processes security operations, password verification, and motor control.
- **Password Security**
  - Users set a 5-digit password.
  - Password is stored securely in EEPROM.
  - Password confirmation required during setup.
- **Door Operations**
  - Correct password unlocks the door.
  - Motor rotates to unlock/lock door with delays.
- **Security Measures**
  - Three consecutive incorrect attempts trigger a 1-minute system lock with a buzzer alert.
  
## 🛠 Hardware Components
- **ATmega32 Microcontrollers** (HMI & Control units)
- **16x2 LCD Display** (for user interface)
- **4x4 Keypad** (for password input)
- **DC Motor** (to control the door lock mechanism)
- **EEPROM** (for password storage)
- **Buzzer** (for security alerts)

## ⚙️ Software Implementation
- **Drivers Used:**
  - GPIO, LCD, Keypad, DC Motor, EEPROM, UART, I2C, Timer, Buzzer.
- **Communication:**
  - `UART`: Handles data transfer between HMI_ECU and Control_ECU.
  - `I2C`: Interfaces with EEPROM for password storage.
- **Interrupt-Driven Design:**
  - Timer1 used for motor control & display timing.
  - Callback-based approach for flexibility.

## 🚀 System Workflow
1. **Password Setup:** User enters and confirms a 5-digit password.
2. **Main Menu:** Provides options to open the door or change the password.
3. **Door Unlocking:** If password matches, motor rotates to unlock & relock.
4. **Password Change:** Requires correct old password before re-entering a new one.
5. **Security Lock:** Three incorrect attempts activate a 1-minute buzzer alert & lock system.

## 🛠 Installation & Usage
1. Clone the repository:
   ```sh
   git clone https://github.com/hnelamir/Embedded_C_projects.git
   ```
2. Compile the project using an AVR-compatible compiler.
3. Flash the firmware onto the ATmega32 microcontrollers.
4. Connect the required hardware components.
5. Run the system and test password authentication.

## 🤝 Contributions
Contributions are welcome! Feel free to improve security features, optimize drivers, or enhance system functionality.

