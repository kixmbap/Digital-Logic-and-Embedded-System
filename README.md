## Arduino Mega2560 Rev3 / Arduino UNO
<img width="300" height="300" alt="image" src="https://github.com/user-attachments/assets/25f6151c-f29a-40ac-b301-cf5f28af273e" />

## สนาม
<img width="1000" height="1000" alt="2" src="https://github.com/user-attachments/assets/a02e5e86-a1db-4ea6-b036-eac4f73f008b" />

---

## 1. Project Overview

**Robot Field Control System** เป็นระบบควบคุมสนามแข่งขันหุ่นยนต์และระบบจับเวลาแบบ Real-time โดยบอร์ด Arduino ทำหน้าที่เป็น Controller หลักสำหรับรับข้อมูลจาก Sensor ต่างๆ ประมวลผลเวลาในการวิ่งของหุ่นยนต์ และสั่งงาน Servo Motor เพื่อควบคุมประตูทั้ง 5 ประตู พร้อมไฟสัญญาณจราจร (Traffic Light) แสดงสถานะ

นอกจากนี้ระบบยังมี **Web Dashboard (Node.js Express + HTML/JS)** สำหรับเชื่อมต่อกับบอร์ด Arduino ผ่าน Serial Port เพื่อดึงข้อมูลสถานะเซนเซอร์ ประตู และเวลาของระบบ มาแสดงผลทางหน้าจอแบบกราฟิกสวยงามและมีระบบเสียงเอฟเฟกต์ประกอบการแข่งขัน

---

## 2. System Features

ระบบสามารถทำงานได้ดังนี้:
* **ควบคุมประตูทั้ง 5 ประตู** ด้วย Servo Motor
* **สวิตช์ควบคุมประตู**:
  * ใช้ Switch 1 สำหรับเปิดประตู 1 (เปิดแล้วเปิดค้าง)
  * ใช้ Switch 2 สำหรับเปิดประตู 4 (เปิดแล้วเปิดค้าง)
* **เลเซอร์เซนเซอร์ควบคุมประตู**:
  * ใช้ Laser 1 ตรวจจับหุ่นยนต์เพื่อเปิดประตู 2 เมื่อพ้นเลเซอร์จะปิดและ Lock ประตู 2 ทันที
  * ใช้ Laser 2 ตรวจจับหุ่นยนต์เพื่อเปิดประตู 3 เมื่อพ้นเลเซอร์จะปิดและ Lock ประตู 3 ทันที
* **ระบบควบคุมประตู 5 อัตโนมัติ**:
  * ประตู 5 เปิดและปิดสลับกันอัตโนมัติทุกๆ 5 วินาที พร้อมไฟแสดงสถานะ LED Traffic Light
  * เมื่อประตู 3 ถูก Lock ประตู 5 จะปิดตัวลงและ Lock ทันที (ไฟสีแดงขึ้นค้าง)
* **ระบบจับเวลาการแข่งข้น (Timer)**:
  * เริ่มต้นจับเวลาอัตโนมัติเมื่อหุ่นยนต์ผ่านเลเซอร์/ตัวรับ IR (IR Sensor)
  * สิ้นสุดการจับเวลาเมื่อหุ่นยนต์วิ่งไปถึงจุดสิ้นสุดและกดสวิตช์ปิดสนาม (SW End)
  * แสดงเวลาแบบนาทีและวินาทีผ่าน Serial Monitor และ Web Dashboard
* **Web Dashboard แบบ Real-time**:
  * เชื่อมต่อบอร์ด Arduino ผ่าน Serial Port เพื่ออ่านข้อมูลสถานะโดยตรง
  * หน้าจอเว็บกราฟิกจำลองสนามการแข่งขันและสถานะเปิด-ปิดของประตูและเลเซอร์
  * ระบบเสียงเอฟเฟกต์ (เสียงเริ่มแข่ง, เสียงวิ่งระหว่างจับเวลา, เสียงเปิดประตูแต่ละบาน, และเสียงเมื่อถึงเส้นชัย)

---

## 3. Hardware & Components

### Main Controller
* Arduino UNO หรือ Arduino Mega2560 Rev3

### Actuators & Indicators
* Servo Motor x5 (ควบคุมประตู 1-5)
* LED Traffic Light Module x1 (หรือ LED แดง เหลือง เขียว) แสดงสถานะประตู 5

### Sensors
* Laser Transmitter x2
* Laser Receiver x2
* Infrared (IR) Sensor x1 (สำหรับตรวจจับจุด Start)

### Input Devices
* Push Button / Switch x3 (เปิดประตู 1, เปิดประตู 4, และสวิตช์หยุดเวลา Finish)

### Other Components
* Jumper Wires
* Breadboard
* Power Supply
* USB Cable (สำหรับเชื่อมต่อ Arduino กับคอมพิวเตอร์เพื่อเปิด Web Dashboard)

---

## 4. Pin Configuration

การกำหนด Pin ของบอร์ด Arduino มีรายละเอียดดังนี้:

### 4.1 Servo Motor (ควบคุมประตู)
| Arduino Pin | Device | Function |
| :---: | :--- | :--- |
| **D2** | Servo Door 1 | ควบคุมประตู 1 |
| **D3** | Servo Door 2 | ควบคุมประตู 2 |
| **D4** | Servo Door 3 | ควบคุมประตู 3 |
| **D5** | Servo Door 4 | ควบคุมประตู 4 |
| **D6** | Servo Door 5 | ควบคุมประตู 5 |

### 4.2 Switches & Inputs
| Arduino Pin | Device | Function | Connection Type |
| :---: | :--- | :--- | :--- |
| **D7** | Switch 1 | ปุ่มเปิดประตู 1 | `INPUT_PULLUP` (กด = LOW, ปล่อย = HIGH) |
| **D8** | Switch 2 | ปุ่มเปิดประตู 4 | `INPUT_PULLUP` (กด = LOW, ปล่อย = HIGH) |
| **D17 (A3)** | Switch End | ปุ่มกดสิ้นสุดเวลา (Finish) | `INPUT_PULLUP` (กด = LOW, ปล่อย = HIGH) |
| **D18 (A4)** | IR Sensor | ตัวรับสัญญาณจุดเริ่มต้น (Start) | `INPUT` (จับเจอวัตถุ = HIGH) |

### 4.3 Laser Sensor
| Arduino Pin | Device | Function |
| :---: | :--- | :--- |
| **D9** | Laser TX 1 | ตัวส่งแสงเลเซอร์ตัวที่ 1 (ประตู 2) |
| **D10** | Laser RX 1 | ตัวรับแสงเลเซอร์ตัวที่ 1 (ประตู 2) |
| **D11** | Laser TX 2 | ตัวส่งแสงเลเซอร์ตัวที่ 2 (ประตู 3) |
| **D12** | Laser RX 2 | ตัวรับแสงเลเซอร์ตัวที่ 2 (ประตู 3) |

### 4.4 LED Traffic (แสดงสถานะประตู 5)
| Arduino Pin | Color | Function |
| :---: | :---: | :--- |
| **D14 (A0)** | Yellow | ติดสว่างเมื่อประตู 5 ปิด (ในช่วงสลับ 5 วินาที) |
| **D15 (A1)** | Green | ติดสว่างเมื่อประตู 5 เปิด (ในช่วงสลับ 5 วินาที) |
| **D16 (A2)** | Red | ติดสว่างค้างเมื่อประตู 5 ถูก Lock (หลังจากประตู 3 ล็อกแล้ว) |

---

## 5. Web Dashboard Setup & Execution

ส่วนควบคุมและแสดงผลเว็บตั้งอยู่ในโฟลเดอร์ `Web Dashbord` พัฒนาด้วย Node.js (Express) ร่วมกับหน้าเว็บ HTML5/Javascript สื่อสารผ่าน Serial Port

### วิธีการติดตั้งและรันระบบ
1. **ติดตั้ง Node.js**: ตรวจสอบให้แน่ใจว่าได้ติดตั้ง Node.js ลงบนคอมพิวเตอร์เรียบร้อยแล้ว
2. **ติดตั้ง Dependencies**:
   เปิด Terminal/Command Prompt แล้วเข้าไปที่ไดเรกทอรี `Web Dashbord` จากนั้นพิมพ์คำสั่ง:
   ```bash
   npm install
   ```
3. **ตรวจสอบพอร์ต Arduino**:
   * ตรวจสอบว่าบอร์ด Arduino เชื่อมต่ออยู่ที่พอร์ตใดของคอมพิวเตอร์ (เช่น `COM7` ใน Windows หรือ `/dev/ttyUSB0` ใน Linux/macOS)
   * เข้าไปแก้ไขพอร์ตในไฟล์ [server.js](file:///K:/Digital-Logic-and-Embedded-System/Web%20Dashbord/server.js) ที่บรรทัดที่ 13:
     ```javascript
     const SERIAL_PORT = "COM7"; // เปลี่ยนให้ตรงกับพอร์ตของคอมพิวเตอร์คุณ
     ```
4. **เริ่มการทำงานของเซิร์ฟเวอร์**:
   พิมพ์คำสั่งรันเซิร์ฟเวอร์:
   ```bash
   node server.js
   ```
5. **เข้าใช้งาน Dashboard**:
   เปิดเว็บบราวเซอร์แล้วไปที่: [http://localhost:3000](http://localhost:3000)

---

## 6. Serial Communication Protocol

Arduino จะส่งข้อมูลผ่าน Serial (Baud Rate: `9600`) มาให้ Web Server ในรูปแบบข้อความดิบ (Raw Text) จากนั้น `server.js` จะทำการ Parsing ข้อความเพื่ออัปเดตสเตตใน Web API `/api/state` ตัวอย่างโปรโตคอลมีดังนี้:

* **สถานะประตู (Doors)**:
  * `DOOR X -> OPEN` : ประตูบานที่ X เปิด
  * `DOOR X -> CLOSED` : ประตูบานที่ X ปิด
  * `DOOR X -> LOCKED` : ประตูบานที่ X ถูกล็อกใช้งานไม่ได้
* **สถานะเลเซอร์ (Lasers)**:
  * `LASER X DETECTED` : เลเซอร์บานที่ X ตรวจพบหุ่นยนต์ผ่าน
  * `LASER X LOST` : เลเซอร์บานที่ X ไม่ตรวจพบสัญญาณเลเซอร์ (หุ่นยนต์พ้นระยะบานนั้น)
* **สถานะปุ่มกด (Switches)**:
  * `SWITCH 1` : สวิตช์ประตู 1 ถูกกด
  * `SWITCH 2` : สวิตช์ประตู 4 ถูกกด
* **ระบบเวลาจับเวลา (Timer)**:
  * `Time start now. (timestamp)` : เริ่มต้นการจับเวลาสนามแข่งขัน
  * `Time end. using X minutes Y seconds` : สิ้นสุดการจับเวลาการแข่งขันและแสดงผลเวลาสุทธิ
  * `Time : X seconds` หรือ `Time : M:SS` : ส่งเวลาอัพเดตรายวินาทีเพื่อแสดงผลบนเว็บและเล่นเสียงประกอบ
