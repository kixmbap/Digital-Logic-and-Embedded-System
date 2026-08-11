## Arduino Mega2560 Rev3
<img width="300" height="300" alt="image" src="https://github.com/user-attachments/assets/25f6151c-f29a-40ac-b301-cf5f28af273e" />

## สนาม
<img width="1000" height="1000" alt="2" src="https://github.com/user-attachments/assets/a02e5e86-a1db-4ea6-b036-eac4f73f008b" />


## 1. Project Overview

Robot Field Control System เป็นระบบควบคุมสนามแข่งขันหุ่นยนต์ โดย Arduino UNO ทำหน้าที่เป็น Controller หลักสำหรับรับข้อมูลจาก Sensor และสั่งงาน Servo Motor เพื่อควบคุมประตูทั้งหมด 5 ประตู

ระบบประกอบด้วย

- Servo Motor จำนวน 5 ตัว
- Laser Transmitter จำนวน 2 ตัว
- Laser Receiver จำนวน 2 ตัว
- Switch จำนวน 2 ตัว
- Arduino UNO จำนวน 1 ตัว

การทำงานของระบบแบ่งออกเป็น 5 ประตู โดยแต่ละประตูมีเงื่อนไขการทำงานแตกต่างกัน

---

## 2. System Features

ระบบสามารถทำงานได้ดังนี้

- ควบคุมประตูทั้งหมด 5 ประตูด้วย Servo Motor
- ใช้ Switch สำหรับเปิดประตู 1
- ใช้ Switch สำหรับเปิดประตู 4
- ใช้ Laser Sensor สำหรับควบคุมประตู 2
- ใช้ Laser Sensor สำหรับควบคุมประตู 3
- ประตูที่ถูก Lock จะไม่สามารถเปิดได้อีกจนกว่าจะ Reset ระบบ
- ประตู 5 สามารถเปิดและปิดอัตโนมัติทุก 5 วินาที
- เมื่อประตู 3 ถูก Lock ประตู 5 จะถูกปิดและ Lock
- เมื่อ Reset Arduino ระบบจะเริ่มต้นสถานะใหม่ทั้งหมด
- แสดงสถานะการทำงานผ่าน Serial Monitor

---

## 3. Hardware

### Main Controller

- Arduino UNO

### Actuators

- Servo Motor x5

### Sensors

- Laser Transmitter x2
- Laser Receiver x2

### Input Devices

- Push Button / Switch x2

### Other Components

- Jumper Wire
- Breadboard
- Power Supply
- USB Cable

---

## 4. Pin Configuration

การกำหนด Pin ถูกแบ่งออกเป็นกลุ่มเพื่อให้ง่ายต่อการต่อวงจรและการพัฒนาโปรแกรม

---

### 4.1 Servo Motor

| Arduino Pin | Device | Function |
|---|---|---|
| D2 | Servo Door 1 | ควบคุมประตู 1 |
| D3 | Servo Door 2 | ควบคุมประตู 2 |
| D4 | Servo Door 3 | ควบคุมประตู 3 |
| D5 | Servo Door 4 | ควบคุมประตู 4 |
| D6 | Servo Door 5 | ควบคุมประตู 5 |

---

### 4.2 Switch

| Arduino Pin | Device | Function |
|---|---|---|
| D7 | Switch 1 | เปิดประตู 1 |
| D8 | Switch 2 | เปิดประตู 4 |

Switch ใช้การเชื่อมต่อแบบ `INPUT_PULLUP`

ดังนั้นสถานะของ Switch คือ

| State | Value |
|---|---|
| ไม่กด | HIGH |
| กด | LOW |

---

### 4.3 Laser Sensor 1

Laser Sensor 1 ใช้สำหรับควบคุมประตู 2

| Arduino Pin | Device | Function |
|---|---|---|
| D9 | Laser TX 1 | ส่งลำแสง Laser |
| D10 | Laser RX 1 | รับและตรวจจับลำแสง |

