# Switch Test

โปรแกรมสำหรับทดสอบ Push Button หรือ Switch

## Objective

ตรวจสอบว่า Arduino สามารถอ่านสถานะของ Switch ได้ถูกต้อง

## Hardware

- Arduino UNO
- Push Button / Switch
- Jumper Wire

## Pin Configuration

| Arduino Pin | Device |
|---|---|
| D7 | Switch |
| GND | Switch GND |

## Wiring

ต่อ Switch ระหว่าง Pin D7 และ GND

```text
Arduino D7
    |
    |
  Switch
    |
    |
   GND
```

โปรแกรมใช้ INPUT_PULLUP

## Switch Logic

| Switch | Arduino Value |
|---|---|
| RELEASED | HIGH |
| PRESSED | LOW |

## การทำงาน

เมื่อไม่กด Switch

```
SWITCH RELEASED
```

เมื่อกด Switch

```
SWITCH PRESSED
```

## Serial Monitor

Baud Rate

```
9600
```

## Expected Result

เมื่อกด Switch ต้องเปลี่ยนจาก

```
SWITCH RELEASED
```

เป็น

```
SWITCH PRESSED
```

เมื่อปล่อย Switch ต้องกลับเป็น

```
SWITCH RELEASED
```

## Result

- [ ] Switch อ่านค่าได้
- [ ] กดแล้วเป็น LOW
- [ ] ปล่อยแล้วเป็น HIGH
- [ ] Serial Monitor แสดงผลถูกต้อง
