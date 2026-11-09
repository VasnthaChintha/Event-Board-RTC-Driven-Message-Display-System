# EventBoard: RTC-Driven Message Display System using LPC2148

## 1. Project Overview

EventBoard is an embedded system project that automatically displays predefined messages on a 16x2 LCD at specific times using the Real-Time Clock (RTC) available in the LPC2148 microcontroller.

The system provides a password-protected Admin Mode that allows authorized users to edit the current time and select which messages should be displayed during the day.

It also monitors room temperature using an LM35 temperature sensor and displays the real-time clock and temperature when no scheduled message is active.

## 2. Objectives

- Automatically display predefined messages at scheduled times.
- Implement RTC-based scheduling using the LPC2148 microcontroller.
- Provide password-protected administrator access.
- Allow users to edit RTC time through an interactive interface.
- Allow administrators to enable or disable scheduled messages.
- Display scrolling messages on a 16x2 LCD.
- Monitor room temperature using an LM35 sensor.
- Indicate the operating status using LEDs.

## 3. Hardware Requirements

| Component | Purpose |
|---|---|
| LPC2148 | Main microcontroller |
| 16x2 LCD | Display messages, time and temperature |
| Keypad | User input and password entry |
| Switch | Enter Admin Mode |
| Green LED | Indicates scheduled message display |
| Red LED | Indicates idle display mode |
| LM35 | Temperature measurement |
| Buzzer | Additional hardware component |

## 4. Software Requirements

- Programming Language: Embedded C
- IDE / Compiler: Keil C Compiler
- Flashing Tool: Flash Magic
- Microcontroller: LPC2148

## 5. System Architecture

The LPC2148 acts as the central controller and coordinates the RTC, LCD, keypad, LEDs and temperature sensor.

The system consists of two operating modes:

### Normal Mode
- Continuously monitors the RTC time.
- Checks whether any enabled message matches the scheduled time.
- Displays the corresponding message on the LCD with scrolling.
- Turns ON the green LED when a scheduled message is displayed.
- If no message is scheduled, displays the current time and room temperature.
- Turns ON the red LED during idle display mode.

### Admin Mode
- Entered using a switch.
- Requires password authentication.
- Provides options to edit the current RTC time.
- Allows users to select which predefined messages should be active.
- Initially, all messages are enabled.

## 6. Working Principle

1. The LPC2148 initializes the peripherals and RTC.
2. The system loads the predefined messages stored in controller memory.
3. The RTC continuously maintains the current time.
4. The controller compares the RTC time with the scheduled message times.
5. If an enabled message matches the current time, it is displayed on the LCD.
6. The LCD scrolls the message to display the complete text.
7. The green LED indicates active schedule display.
8. If no scheduled message matches, the LCD displays the current time and room temperature.
9. The red LED indicates idle display mode.
10. Authorized users can enter Admin Mode to modify the time and message selection.

## 7. Message Scheduling

The system supports 10 predefined messages stored in the microcontroller's memory.

Each message contains:

- Hour
- Minute
- Message text
- Enable/Disable status

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

Here:
- `hour`: Scheduled hour.
- `minute`: Scheduled minute.
- `text`: Message to be displayed.
- `enabled`: 1 means enabled; 0 means disabled.

### Predefined Messages

| Time | Scheduled Message |
|---|---|
| 07:45 | Good Morning! Classes Start Soon |
| 13:45 | C Programming Session in Classroom number 2 |
| 10:15 | C module theory exam in 4th floor lab1 |
| 10:15 | C module lab exam in 4th floor lab2 and middle lab at 10:30AM |
| 12:45 | Lunch Break from 1PM – 2PM |
| 09:45 | ARM Workshop on external interrupts in LAB1 at 10AM |
| 09:45 | ARM kit issue time from 10AM – 10:30AM in middle lab |
| 15:15 | Only 15 mins break time for next ARM session |
| 17:00 | Revise today's Class programs at home! |
| 17:45 | End of Day – See You Tomorrow! |

Initially, all messages are selected.

## 8. Key Features

- RTC-based automatic message scheduling.
- Password-protected Admin Mode.
- Interactive RTC time editing.
- User-controlled message selection.
- Scrolling text display on a 16x2 LCD.
- Temperature monitoring using LM35.
- LED-based status indication.
- Multiple predefined messages stored in controller memory.

## 9. Applications

- Educational institutions.
- Classroom announcement systems.
- Laboratories and workshops.
- Office announcement boards.
- Scheduled information display systems.

## 10. Future Enhancements

- Add an EEPROM-based configuration storage mechanism.
- Support dynamic message updates.
- Add wireless communication for remote message management.
- Implement a real-time calendar-based scheduling system.
- Add additional display interfaces.

## 11. Technologies Used

- Embedded C
- LPC2148 ARM7 Microcontroller
- Real-Time Clock (RTC)
- 16x2 LCD
- Keypad Interfacing
- ADC Interfacing
- LM35 Temperature Sensor
- GPIO and Peripheral Interfacing

## 12. Conclusion

The EventBoard project demonstrates the implementation of an RTC-driven automated message display system using the LPC2148 microcontroller.

It combines embedded C programming, peripheral interfacing, real-time scheduling, password-protected administration and temperature monitoring into a single embedded application.

The project provides a practical demonstration of microcontroller-based automation and real-time information display.

---

**Project:** EventBoard – RTC-Driven Message Display System  
**Microcontroller:** LPC2148 (ARM7)  
**Programming Language:** Embedded C  
**Development Tool:** Keil C Compiler  
**Flashing Tool:** Flash Magic
