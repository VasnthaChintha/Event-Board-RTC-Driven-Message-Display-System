📢 EventBoard: RTC-Driven Message Display System using LPC2148

📖 Table of Contents
- Project Overview
- Problem Statement
- Proposed Solution
- Objectives
- Features
- Hardware Requirements
- Software Requirements
- Block Diagram
- Working Principle
- Normal Operating Mode
- Admin Mode
- Message Scheduling
- RTC Time Editing
- Temperature Monitoring
- Software Modules
- Results
- Applications
- Advantages
- Future Enhancements
- Learning Outcomes
- Conclusion

📖 Project Overview

EventBoard is an Embedded Systems project developed to automate the display of predefined announcements at scheduled times using the LPC2148 ARM7 Microcontroller.
The system uses the built-in Real-Time Clock (RTC) to maintain the current time and automatically display scheduled messages on a 16x2 LCD with a scrolling mechanism. The system supports 10 predefined messages stored in the microcontroller's memory. Users can enter a secure Admin Mode using a switch and password-protected keypad to edit the current time and select which messages should be active. When a scheduled message matches the RTC time, the corresponding message is displayed on the LCD, and a green LED indicates active schedule display mode. When no message is scheduled, the system displays the current time and room temperature measured using an LM35 temperature sensor through the LPC2148 ADC. A red LED indicates idle display mode. This project demonstrates practical implementation of Embedded C programming, ARM7 microcontroller interfacing, RTC-based scheduling, keypad interfacing, LCD interfacing, ADC operations, and password-based authentication.

❗ Problem Statement

Traditional notice boards require manual updates whenever announcements, schedules, or important information change. 
This process consumes time and requires continuous human intervention. Additionally, users may miss important announcements if they are not present near the notice board at the time of display. There is a need for an automated, real-time message display system that can display predefined announcements at specific times without requiring manual intervention.

💡 Proposed Solution

This project introduces an RTC-driven automated message display system using the LPC2148 microcontroller. The system stores predefined messages in controller memory and uses the RTC to compare the current time with scheduled message timings. When a scheduled time matches, the corresponding message is automatically displayed on the 16x2 LCD with scrolling functionality. A password-protected Admin Mode allows authorized users to edit the RTC time and enable or disable messages using a keypad. The system also integrates an LM35 temperature sensor to monitor room temperature and display it whenever no scheduled announcement is active.

🎯 Objectives

- Automate the display of predefined announcements.
- Implement RTC-based scheduling using LPC2148.
- Display messages at specific hours and minutes.
- Provide scrolling text functionality on a 16x2 LCD.
- Implement password-protected Admin Mode.
- Allow interactive RTC time editing.
- Enable or disable scheduled messages through a keypad.
- Monitor room temperature using an LM35 sensor.
- Indicate operating status using green and red LEDs.

⭐ Features

- RTC-Based Automatic Message Scheduling
- 10 Predefined Messages
- 16x2 LCD Scrolling Display
- Password-Protected Admin Mode
- Keypad-Based User Interaction
- Interactive RTC Time Editing
- Enable/Disable Message Selection
- LM35 Temperature Monitoring
- ADC-Based Temperature Measurement
- Green LED for Active Schedule Display
- Red LED for Idle Display Mode
- Modular Embedded C Programming

🧩 Hardware Requirements

<img width="631" height="566" alt="Screenshot 2026-11-09 171705" src="https://github.com/user-attachments/assets/2fc1691d-69ab-4079-b8ec-2144b7fd1a1b" />

💻 Software Requirements

- Embedded C Programming
- Keil uVision IDE
- Keil C Compiler
- Flash Magic
- LPC2148 Microcontroller Programming

🖼️ Block Diagram


The following block diagram illustrates the interaction between the LPC2148 microcontroller and its input/output peripherals.

![EventBoard Block Diagram](Circuit_Diagram/EventBoard_Block_Diagram.png)

📸 Project Hardware

<img width="4095" height="1676" alt="1000400154" src="https://github.com/user-attachments/assets/b65e2976-0687-40d5-bcbf-d0ccf3579000" />

Main Controller

**LPC2148 ARM7 Microcontroller**

The LPC2148 acts as the central processing unit and controls all the connected peripherals.
Input Components
- Matrix Keypad – Password entry and message selection.
- Switch – Admin Mode activation.
- RTC – Provides the current time.
- LM35 – Measures room temperature.
  
Output Components

- 16x2 LCD – Displays scheduled messages, time and temperature.
- Green LED – Indicates active scheduled message display.
- Red LED – Indicates idle display mode.
- Buzzer – Additional alert hardware.

⚙️ Working Principle

Step 1 – System Initialization

The LPC2148 initializes the required peripherals, including:
- LCD
- RTC
- Keypad
- GPIO
- ADC
- LEDs
The controller loads the predefined messages from its memory.

Step 2 – RTC Time Monitoring

The RTC continuously maintains the current time.
The controller reads the RTC hour and minute values and compares them with the predefined message schedules.

Step 3 – Message Scheduling

The system contains 10 predefined messages.
Each message contains:
- Hour
- Minute
- Message text
- Enable/Disable status
When the current RTC time matches an enabled message's scheduled time, the corresponding message is selected for display.

Step 4 – LCD Message Display

When a scheduled message is identified:
- The message is displayed on the 16x2 LCD.
- The message scrolls to display the complete text.
- The green LED is turned ON to indicate active schedule display mode.

Step 5 – Idle Display Mode

When no scheduled message is active:
- The LCD displays the current RTC time.
- The LM35 sensor measures room temperature.
- The LPC2148 ADC reads the sensor output.
- The measured temperature is displayed on the LCD.
- The red LED is turned ON to indicate idle mode.
- 
🔐 Admin Mode

Admin Mode provides authorized access to modify system settings.

 Admin Mode Activation
 
1. Activate the Admin Mode switch.
2. The system requests a password.
3. Enter the password using the keypad.
4. The controller verifies the entered password.
5. After successful authentication, Admin Mode is enabled.

Admin Mode Operations

- Edit current RTC time.
- Select predefined messages.
- Enable selected messages.
- Disable unwanted messages.
- Return to Normal Mode.
Initially, all 10 predefined messages are enabled.

⏰ RTC Time Editing

The RTC time editing feature is designed to provide a fully user-interactive experience.

The administrator can modify the current time through the keypad.

### Time Editing Process

1. Enter Admin Mode.
2. Complete password authentication.
3. Select the RTC Time Editing option.
4. Enter the required hour.
5. Enter the required minute.
6. Confirm the entered time.
7. Update the RTC with the new time.
8. Return to the Admin Menu.
The updated RTC time is used for subsequent message scheduling.

📅 Message Scheduling

The system supports 10 predefined messages stored in controller memory.

### Message Data Structure

```c
#define TOTAL_MESSAGES 10

typedef struct
{
    u8 hour;
    u8 minute;
    char text[80];
    u8 enabled;
} Message;
```

### Structure Description

- `hour` – Scheduled hour.
- `minute` – Scheduled minute.
- `text` – Message content.
- `enabled` – 1 means enabled; 0 means disabled.

### Predefined Messages

<img width="576" height="569" alt="image" src="https://github.com/user-attachments/assets/fdf22b73-9530-499f-8e6f-4639687f90f1" />


**Note:** Initially, all messages are selected.

🌡️ Temperature Monitoring

The LM35 temperature sensor is used to measure the surrounding room temperature.

### Working Process

1. LM35 generates an analog voltage corresponding to temperature.
2. The LPC2148 ADC reads the analog voltage.
3. The controller converts the ADC reading into a temperature value.
4. The measured temperature is displayed on the LCD during idle mode.

# 🧩 Software Modules

The project can be organized into the following software modules:
- Main Control Module
- LCD Driver Module
- RTC Driver Module
- Keypad Driver Module
- Password Authentication Module
- Admin Mode Module
- Message Scheduling Module
- Message Scrolling Module
- ADC Driver Module
- LM35 Temperature Monitoring Module
- LED Control Module
- Buzzer Control Module

📊 Results

The intended system operation includes:
- Automatic display of predefined messages based on RTC time.
- Scrolling announcements on a 16x2 LCD.
- Password-protected administrator access.
- User-controlled message selection.
- Interactive RTC time modification.
- Room temperature monitoring using LM35.
- LED-based indication of active and idle modes.
The implementation demonstrates the integration of multiple LPC2148 peripherals in a real-time embedded application.

🚀 Applications

- Educational Institutions
- Classrooms and Laboratories
- Office Announcement Systems
- Hospitals
- Workshops
- Industrial Information Boards
- Railway and Bus Information Displays
- Automated Notice Boards

✅ Advantages

- Reduces manual announcement updates.
- Automatically displays scheduled information.
- Provides password-protected administrative access.
- Allows flexible message selection.
- Supports real-time clock-based scheduling.
- Provides temperature monitoring.
- Offers simple keypad-based operation.
- Demonstrates practical embedded system integration.

🔮 Future Enhancements

- Add EEPROM storage for messages and configuration.
- Implement wireless message updates using Wi-Fi.
- Add Bluetooth-based message configuration.
- Support dynamic message creation and deletion.
- Integrate a larger LCD or graphical display.
- Add date-based scheduling.
- Implement remote monitoring through a mobile application.
- Add multiple language support.

📚 Learning Outcomes

- ARM7 LPC2148 Microcontroller Programming
- Embedded C Programming
- RTC Interfacing
- LCD Interfacing
- Matrix Keypad Interfacing
- GPIO Programming
- ADC Interfacing
- LM35 Temperature Sensor Interfacing
- Password-Based Authentication
- Real-Time Scheduling
- Peripheral Driver Development
- Embedded System Design

🏁 Conclusion

The EventBoard project demonstrates the development of an automated message display system using the LPC2148 ARM7 microcontroller.
By integrating RTC-based scheduling, LCD scrolling, keypad-based administration, password authentication, and temperature monitoring, the system provides an effective solution for displaying scheduled announcements.
This project provides practical experience in Embedded C programming, ARM7 architecture, peripheral interfacing, and real-time embedded system development.

🛠️ Technologies Used

- **Microcontroller:** LPC2148 (ARM7)
- **Programming Language:** Embedded C
- **Display:** 16x2 LCD
- **Temperature Sensor:** LM35
- **Input Device:** Matrix Keypad and Switch
- **Development IDE:** Keil uVision
- **Programming Tool:** Flash Magic

🙏 Acknowledgement

This project was developed as an Embedded Systems application to demonstrate RTC-based automated message scheduling, secure administration, LCD interfacing, and temperature monitoring using the LPC2148 ARM7 microcontroller.

⭐ Thank you for visiting this repository!
