# Servo + Switch Test

โปรแกรมสำหรับทดสอบการทำงานร่วมกันระหว่าง Servo Motor และ Switch

## Objective

ทดสอบว่าเมื่อกด Switch แล้ว Servo สามารถเปิดประตูและเปิดค้างได้

## Hardware

- Arduino UNO
- Servo Motor
- Push Button / Switch

## Pin Configuration

| Pin | Device |
|---|---|
| D2 | Servo Signal |
| D7 | Switch |
| 5V | Servo VCC |
| GND | Servo GND |
| GND | Switch GND |

## Logic

ระบบเริ่มต้นด้วยประตูปิด

```text
RESET
  |
  v
Door CLOSED
  |
  v
Press Switch
  |
  v
Door OPEN
  |
  v
Door remains OPEN
```

ไม่ต้องกด Switch ค้าง

กดเพียงครั้งเดียวก็เปิดประตู

## Reset

เมื่อ Reset Arduino

```
Door CLOSED
```

และสามารถกด Switch เพื่อเปิดใหม่ได้

## Serial Monitor

Baud Rate

```
9600
```

ตัวอย่าง

```
=== SERVO + SWITCH TEST ===
Door CLOSED
System Ready
SWITCH PRESSED
DOOR OPEN
```

## Expected Result

1. เริ่มต้น Servo อยู่ที่ 0°
2. กด Switch
3. Servo หมุนไป 90°
4. Servo เปิดค้าง
5. Reset
6. Servo กลับไป 0°

## Result

- [ ] Servo ทำงาน
- [ ] Switch ทำงาน
- [ ] กด Switch แล้ว Servo เปิด
- [ ] ไม่ต้องกด Switch ค้าง
- [ ] Servo เปิดค้าง
- [ ] Reset แล้ว Servo กลับมาปิด
