# Servo Test

โปรแกรมสำหรับทดสอบ Servo Motor เพียง 1 ตัว ก่อนนำไปใช้งานร่วมกับอุปกรณ์อื่น

## Objective

ตรวจสอบว่า Servo Motor สามารถหมุนไปยังตำแหน่ง OPEN และ CLOSED ได้ถูกต้อง

## Hardware

- Arduino UNO
- Servo Motor
- Jumper Wire

## Pin Configuration

| Arduino Pin | Device |
|---|---|
| D2 | Servo Signal |
| 5V | Servo VCC |
| GND | Servo GND |

## Servo Position

| Angle | Status |
|---|---|
| 0° | CLOSED |
| 90° | OPEN |

## การทำงาน

เมื่อเริ่มระบบ Servo จะอยู่ที่ตำแหน่ง CLOSED

จากนั้นทำงานตามลำดับ

```text
CLOSED
   |
2 seconds
   |
OPEN
   |
2 seconds
   |
CLOSED
   |
Repeat
```

## Serial Monitor

ตั้ง Baud Rate เป็น

```
9600
```

ตัวอย่าง

```
=== SERVO TEST ===
Door CLOSED
Door OPEN
Door CLOSED
Door OPEN
```

## Expected Result

Servo ต้องสามารถหมุนระหว่าง

```
0° <-> 90°
```

ได้อย่างถูกต้อง

หาก Servo ทำงานผิดปกติ ควรแก้ไขก่อนเข้าสู่ Test ถัดไป

## Result

- [ ] Servo เปิดได้
- [ ] Servo ปิดได้
- [ ] Servo หมุนถูกทิศทาง
- [ ] Servo ไม่สั่นผิดปกติ
