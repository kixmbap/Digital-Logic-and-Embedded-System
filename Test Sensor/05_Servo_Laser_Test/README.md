# Servo + Laser Test

โปรแกรมสำหรับทดสอบการทำงานร่วมกันระหว่าง Servo Motor และ Laser Sensor

Test นี้จำลองการทำงานของประตูที่เปิดเมื่อ Laser ตรวจพบ และปิด Lock เมื่อ Laser ขาดการตรวจจับ

## Objective

ตรวจสอบ Logic ของประตูที่ใช้ Laser Sensor เป็นตัวควบคุม

## Hardware

- Arduino UNO
- Servo Motor
- Laser Transmitter
- Laser Receiver

## Pin Configuration

| Pin | Device |
|---|---|
| D3 | Servo Signal |
| D9 | Laser TX |
| D10 | Laser RX |
| 5V | VCC |
| GND | GND |

## Logic

ระบบเริ่มต้นด้วยประตูปิด

```text
RESET
  |
  v
Door CLOSED
  |
  v
Laser DETECTED
  |
  v
Door OPEN
  |
  v
Laser LOST
  |
  v
Door CLOSED
  |
  v
Door LOCKED
```

## Laser Detected

เมื่อ Laser ถูกตรวจพบ

```
LASER DETECTED
       |
       v
DOOR OPEN
```

## Laser Lost

เมื่อ Laser ขาดการตรวจจับ

```
LASER LOST
     |
     v
DOOR CLOSED
     |
     v
DOOR LOCKED
```

หลังจาก Lock แล้ว ต่อให้ Laser กลับมา

```
LASER DETECTED
```

ประตูจะยังคงปิด

## Reset

การ Reset Arduino จะล้างสถานะ Lock

```
RESET
  |
  +-- Door CLOSED
  |
  +-- Door UNLOCKED
```

จากนั้นระบบสามารถเริ่มทำงานใหม่

## Serial Monitor

Baud Rate

```
9600
```

ตัวอย่าง

```
=== SERVO + LASER TEST ===
Door CLOSED
System Ready
LASER DETECTED
DOOR OPEN
LASER LOST
DOOR CLOSED
DOOR LOCKED
```

## Expected Result

- [ ] เริ่มต้นประตูปิด
- [ ] Laser ตรวจพบ
- [ ] ประตูเปิด
- [ ] Laser ขาด
- [ ] ประตูปิด
- [ ] ประตู Lock
- [ ] Laser กลับมาแล้วประตูไม่เปิด
- [ ] Reset แล้วสามารถเริ่มใหม่ได้
