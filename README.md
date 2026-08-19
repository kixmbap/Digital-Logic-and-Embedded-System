## Arduino Mega2560 Rev3 / Arduino UNO
<img width="300" height="300" alt="image" src="https://github.com/user-attachments/assets/25f6151c-f29a-40ac-b301-cf5f28af273e" />

**รูปสนามจริง (ภาพรวมทั้งหมด)**
<img width="1000" height="1500" alt="image" src="https://github.com/user-attachments/assets/133459f0-1b3a-4bd6-a419-bb44a4c91cf7" />


---

## 1. Project Overview

**Robot Field Control System** เป็นระบบควบคุมสนามแข่งขันหุ่นยนต์และระบบจับเวลาแบบ Real-time โดยบอร์ด Arduino (สเก็ตช์ล่าสุด `MainCodeV4`) ทำหน้าที่เป็น Controller หลักสำหรับรับข้อมูลจาก Sensor ต่างๆ ประมวลผลเวลาในการวิ่งของหุ่นยนต์ และสั่งงาน Servo Motor เพื่อควบคุมประตูทั้ง 5 ประตู พร้อมไฟสัญญาณจราจร (Traffic Light) แสดงสถานะ

นอกจากนี้ระบบยังมี **Web Dashboard V3 (Node.js Express + HTML/JS)** สำหรับเชื่อมต่อกับบอร์ด Arduino ผ่าน Serial Port เพื่อดึงข้อมูลสถานะเซนเซอร์ ประตู และเวลาของระบบ มาแสดงผลทางหน้าจอแบบกราฟิกสวยงามและมีระบบเสียงเอฟเฟกต์ประกอบการแข่งขัน โดยแยกเป็น 2 หน้าจอ คือ หน้าควบคุม/แสดงผลสนาม (`index.html`) และหน้าพากย์ผลผู้ชนะ (`dashboard.html`)

---

## 2. System Features

ระบบสามารถทำงานได้ดังนี้:
* **ควบคุมประตูทั้ง 5 ประตู** ด้วย Servo Motor
* **สวิตช์ควบคุมประตู**:
  * ใช้ Switch 1 สำหรับเปิดประตู 1 (เปิดแล้วเปิดค้าง)
  * ใช้ Switch 2 สำหรับเปิดประตู 4 (เปิดแล้วเปิดค้าง)
* **IR/เลเซอร์เซนเซอร์ควบคุมประตู**:
  * ใช้ IR 1 ตรวจจับหุ่นยนต์เพื่อเปิดและ Lock ประตู 2 ทันทีที่ตรวจพบ
  * ใช้ IR 2 ตรวจจับหุ่นยนต์ (หลังประตู 4 เปิดแล้ว) เพื่อเปิดประตู 3 **และ** Lock ประตู 5 ให้ปิดค้างพร้อมไฟแดงในเวลาเดียวกัน
* **ระบบไฟจราจร (Traffic Light) ควบคุมประตู 5 อัตโนมัติ**:
  * วนสถานะ แดง (ปิดประตู 5, ค้าง 5 วินาที) → เขียว (เปิดประตู 5, ค้าง 2.5 วินาที) → เหลือง (เตรียมปิด, ค้าง 2.5 วินาที) → กลับไปแดง
  * เมื่อ IR 1 ตรวจพบหุ่นยนต์ (Door 2 Locked) ไฟจะค้างเขียวและเปิดประตู 5 ค้างไว้จนกว่า IR 2 จะทำงาน
  * เมื่อ IR 2 ตรวจพบหุ่นยนต์ (หลัง Door 4 เปิด) ประตู 5 จะปิดตัวลงและ Lock ทันที พร้อมไฟแดงค้าง
* **ระบบจับเวลาการแข่งขัน (Timer)**:
  * เริ่มต้นจับเวลาอัตโนมัติเมื่อหุ่นยนต์ผ่านตัวรับ IR จุด Start
  * สิ้นสุดการจับเวลาเมื่อหุ่นยนต์วิ่งไปถึงจุดสิ้นสุดและกดสวิตช์ปิดสนาม (SW End)
  * แสดงเวลาแบบนาทีและวินาทีผ่าน Serial Monitor และ Web Dashboard
* **คำสั่งรีเซ็ตสนาม**:
  * ส่งอักษร `R` ผ่าน Serial (จาก Serial Monitor หรือปุ่ม Reset บนเว็บ) เพื่อปิด/ล็อกประตูทั้งหมดกลับสู่ค่าเริ่มต้นและรีเซ็ตตัวจับเวลาโดยไม่ต้องอัปโหลดโค้ดใหม่
* **Web Dashboard แบบ Real-time**:
  * เชื่อมต่อบอร์ด Arduino ผ่าน Serial Port เพื่ออ่านข้อมูลสถานะโดยตรง
  * หน้า `index.html`: กราฟิกจำลองสนามการแข่งขันและสถานะเปิด-ปิดของประตู, เลเซอร์/IR และไฟจราจร พร้อมปุ่มสั่งรีเซ็ตสนาม
  * หน้า `dashboard.html`: หน้าพากย์/โพเดียมแสดงผลสรุปการแข่งขัน
  * ระบบเสียงเอฟเฟกต์ (เสียงเริ่มแข่ง, เสียงวิ่งระหว่างจับเวลา, เสียงเปิด/ปิดประตูแต่ละบาน, และเสียงเมื่อถึงเส้นชัย)

---

## 3. Hardware & Components

### Main Controller
* Arduino UNO หรือ Arduino Mega2560 Rev3

### Actuators & Indicators
* Servo Motor x5 (ควบคุมประตู 1-5)
* LED Traffic Light Module x1 (หรือ LED แดง เหลือง เขียว) แสดงสถานะประตู 5

### Sensors
* IR / Laser Receiver x2 (ตรวจจับหุ่นยนต์เพื่อควบคุมประตู 2, 3 และ 5)
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

การกำหนด Pin ของบอร์ด Arduino (อิงตาม `MainCodeV4/MainCodeV4.ino`) มีรายละเอียดดังนี้:

### 4.1 Servo Motor (ควบคุมประตู)
| Arduino Pin | Device | Function |
| :---: | :--- | :--- |
| **D2** | Servo Door 1 | ควบคุมประตู 1 |
| **D3** | Servo Door 2 | ควบคุมประตู 2 |
| **D13** | Servo Door 3 | ควบคุมประตู 3 |
| **D5** | Servo Door 4 | ควบคุมประตู 4 |
| **D6** | Servo Door 5 | ควบคุมประตู 5 |

### 4.2 Switches & Inputs
| Arduino Pin | Device | Function | Connection Type |
| :---: | :--- | :--- | :--- |
| **D7** | Switch 1 | ปุ่มเปิดประตู 1 | `INPUT_PULLUP` (กด = LOW, ปล่อย = HIGH) |
| **D8** | Switch 2 | ปุ่มเปิดประตู 4 | `INPUT_PULLUP` (กด = LOW, ปล่อย = HIGH) |
| **D17 (A3)** | Switch End | ปุ่มกดสิ้นสุดเวลา (Finish) | `INPUT_PULLUP` (กด = LOW, ปล่อย = HIGH) |
| **D18 (A4)** | IR Sensor | ตัวรับสัญญาณจุดเริ่มต้น (Start) | `INPUT` (จับเจอวัตถุ = HIGH) |

### 4.3 IR / Laser Receiver (ตรวจจับหุ่นยนต์)
| Arduino Pin | Device | Function |
| :---: | :--- | :--- |
| **D9** | IR 1 | ตรวจจับหุ่นยนต์เพื่อเปิด/ล็อกประตู 2 |
| **D10** | IR 2 | ตรวจจับหุ่นยนต์เพื่อเปิดประตู 3 และล็อกปิดประตู 5 |

### 4.4 LED Traffic (แสดงสถานะประตู 5)
| Arduino Pin | Color | Function |
| :---: | :---: | :--- |
| **D14 (A0)** | Yellow | ติดสว่างระหว่างช่วงเตรียมปิดประตู 5 |
| **D15 (A1)** | Green | ติดสว่างเมื่อประตู 5 เปิด |
| **D16 (A2)** | Red | ติดสว่างเมื่อประตู 5 ปิด/ถูก Lock |

---

## 5. Project Structure

| Path | Description |
| :--- | :--- |
| `MainCodeV4/` | สเก็ตช์ Arduino เวอร์ชันล่าสุดที่ใช้งานจริง |
| `MainCode/` | สเก็ตช์เวอร์ชันเก่า (เก็บไว้อ้างอิง) |
| `Web Dashbord V3/` | เว็บแดชบอร์ด (Node.js + Express) เวอร์ชันล่าสุด |
| `Test Sensor/` | สเก็ตช์ทดสอบอุปกรณ์ย่อย (Servo, Switch, Laser/IR ฯลฯ) |
| `or version/` | เก็บโค้ดและเว็บแดชบอร์ดเวอร์ชันก่อนหน้าทั้งหมด |
| `map1.jpg` | ภาพผังสนามแข่งขัน |

---

## 6. Web Dashboard Setup & Execution

ส่วนควบคุมและแสดงผลเว็บตั้งอยู่ในโฟลเดอร์ **`Web Dashbord V3`** พัฒนาด้วย Node.js (Express) ร่วมกับหน้าเว็บ HTML5/Javascript สื่อสารผ่าน Serial Port

### วิธีการติดตั้งและรันระบบ
1. **ติดตั้ง Node.js**: ตรวจสอบให้แน่ใจว่าได้ติดตั้ง Node.js ลงบนคอมพิวเตอร์เรียบร้อยแล้ว
2. **ติดตั้ง Dependencies**:
   เปิด Terminal/Command Prompt แล้วเข้าไปที่ไดเรกทอรี `Web Dashbord V3` จากนั้นพิมพ์คำสั่ง:
   ```bash
   npm install
   ```
3. **ตรวจสอบพอร์ต Arduino**:
   * ตรวจสอบว่าบอร์ด Arduino เชื่อมต่ออยู่ที่พอร์ตใดของคอมพิวเตอร์ (เช่น `COM7` ใน Windows หรือ `/dev/ttyUSB0` ใน Linux/macOS)
   * เข้าไปแก้ไขพอร์ตในไฟล์ `server.js` ที่บรรทัดที่ 13:
     ```javascript
     const SERIAL_PORT = "COM7"; // เปลี่ยนให้ตรงกับพอร์ตของคอมพิวเตอร์
     ```
4. **เริ่มการทำงานของเซิร์ฟเวอร์**:
   พิมพ์คำสั่งรันเซิร์ฟเวอร์:
   ```bash
   node server.js
   ```
5. **เข้าใช้งาน Dashboard**:
   * หน้าควบคุม/แสดงผลสนาม: [http://localhost:3000](http://localhost:3000) (`index.html`)
   * หน้าพากย์/โพเดียมผลการแข่งขัน: [http://localhost:3000/dashboard.html](http://localhost:3000/dashboard.html)
6. **รีเซ็ตสนามจากหน้าเว็บ**: กดปุ่ม Reset บนหน้าเว็บเพื่อยิง `POST /api/reset` ซึ่งจะส่งอักษร `R` ไปยัง Arduino และเคลียร์สถานะฝั่งเซิร์ฟเวอร์

### ภาพหน้าจอ Web Dashboard

**หน้า Robot Field Dashboard (`index.html`)**
<img width="1000" height="1500" alt="image" src="https://github.com/user-attachments/assets/fd1f995e-5d68-4ed0-8cad-317d53ee4657" />


**หน้า Podium Dashboard (`dashboard.html`)**
<img width="1000" height="1500" alt="image" src="https://github.com/user-attachments/assets/4de8e581-1086-4915-8cb5-e6ca6f658a6b" />


---

## 7. Serial Communication Protocol

Arduino จะส่งข้อมูลผ่าน Serial (Baud Rate: `9600`) มาให้ Web Server ในรูปแบบข้อความดิบ (Raw Text) จากนั้น `server.js` จะทำการ Parsing ข้อความเพื่ออัปเดตสเตตใน Web API `/api/state` ตัวอย่างโปรโตคอลมีดังนี้:

* **สถานะประตู (Doors)**:
  * `DOOR X -> OPEN` : ประตูบานที่ X เปิด
  * `DOOR X -> CLOSED` : ประตูบานที่ X ปิด
  * `DOOR X -> LOCKED` : ประตูบานที่ X ถูกล็อกใช้งานไม่ได้ (Door 2 และ Door 5)
* **สถานะไฟจราจร (Traffic Light)**:
  * `LIGHT -> RED` / `LIGHT -> YELLOW` / `LIGHT -> GREEN` : สถานะไฟที่กำลังติดสว่าง ณ ขณะนั้น
* **สถานะปุ่มกด (Switches)**:
  * `SWITCH 1` : สวิตช์ประตู 1 ถูกกด
  * `SWITCH 2` : สวิตช์ประตู 4 ถูกกด
* **ระบบเวลาจับเวลา (Timer)**:
  * `Time start now. (timestamp)` : เริ่มต้นการจับเวลาสนามแข่งขัน
  * `Time : X seconds` หรือ `Time : M:SS minutes` : ส่งเวลาอัพเดตรายวินาทีเพื่อแสดงผลบนเว็บและเล่นเสียงประกอบ
  * `Time end. using X minutes Y seconds (timestamp)` : สิ้นสุดการจับเวลาการแข่งขันและแสดงผลเวลาสุทธิ
* **ระบบและการรีเซ็ต (System)**:
  * `System Ready` : ระบบพร้อมใช้งาน (ส่งตอน Setup)
  * `SYSTEM_RESET_COMPLETE` : รีเซ็ตสนามเสร็จสมบูรณ์ (ตอบสนองต่อคำสั่ง `R`)
