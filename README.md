# Attendance System Using Arduino

This project demonstrates an **attendance system** built with **Arduino UNO**, an **RFID reader**, an **I2C LCD display**, and a **buzzer**. It records attendance by scanning RFID cards, stores the data in an **Excel sheet**, and provides real-time feedback to users.

## Features

- **RFID-based Authentication**: Scans RFID cards to identify users and grants access.
- **Real-Time Feedback**: Displays user details on the **LCD screen** upon successful authentication.
- **Data Logging**: Attendance data is logged in **CSV format**, which can be opened in **Excel** for easy tracking.
- **Buzzer Feedback**: A buzzer sounds upon successful or unsuccessful card scans.
- **Time Tracking**: Captures the time elapsed since the last scan, and shows the current date and time.

## Components Used

- **Arduino UNO**
- **MFRC522 RFID Reader**
- **I2C LCD Display**
- **Buzzer**
- **RFID Cards**
- **Excel Sheet** for data storage

## Working

- The user presents their **RFID card** to the **reader**.
- If the card is recognized, the **LCD display** shows the user's **name**, **branch**, and **roll number**.
- **Data is logged** in a CSV format, including the **UID** of the scanned card, the **name**, **branch**, **roll number**, **date**, and **time**.
- A **buzzer** provides feedback on the scan result (authorized or denied).
- The system also tracks the **time elapsed** since the last scan.

## Code Overview

- **Libraries**:  
  - `SPI.h`, `MFRC522.h`: For RFID functionality.
  - `Wire.h`, `LiquidCrystal_I2C.h`: For controlling the LCD.
  - `TimeLib.h`: For time management.

- **Key Functions**:
  - **getid()**: Reads the RFID card's UID.
  - **array_to_string()**: Converts the UID array to a string format.
  - **identifyCard()**: Identifies the card and fetches the user's details (e.g., name, branch, roll number).
  - **RTC()**: Displays "Put Your Card to Reader" message on the LCD.
  - **info()**: Displays user information and "Authorized Access" message on the LCD.

## Installation

1. **Hardware Setup**:  
   - Connect the **MFRC522 RFID reader** to the **Arduino UNO** using SPI.
   - Connect the **I2C LCD display** to the Arduino.
   - Connect the **buzzer** to the designated pin (2 in this case).
   
2. **Software Setup**:  
   - Install the following Arduino libraries:  
     - **SPI**  
     - **MFRC522**  
     - **Wire**  
     - **LiquidCrystal_I2C**  
     - **TimeLib**
   - Upload the code to the Arduino using the **Arduino IDE**.

## How to Use
1. Upload the code to the **Arduino UNO**.
2. When the system is powered on, the LCD will display "Put Your Card to Reader".
3. Present an **RFID card** to the reader.  
   - If the card is recognized, the LCD will show the user's **name**, **branch**, and **roll number**.
   - If the card is unrecognized, the LCD will display "Access Denied" and a buzzer will sound.
4. The **time elapsed** since the last scan and the current **date and time** will be logged in **CSV format** to the serial monitor.

## CSV Output Format
The data logged in the CSV format will look like this:
DATA,dd/mm/yyyy,"hh:mm:ss",UID,name,branch,roll_number

## Contributors
- **Aditya Abhilash**
- **Atharva Tol**

## License
This project is open-source. Feel free to use and modify it for your personal or academic projects.
