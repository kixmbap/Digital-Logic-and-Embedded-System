# Dual Laser Test

โปรแกรมสำหรับทดสอบ Laser Sensor จำนวน 2 ชุดพร้อมกัน

## Objective

ตรวจสอบว่า Laser Sensor ทั้งสองชุดสามารถทำงานพร้อมกันได้ และ Arduino สามารถอ่านค่าจาก Receiver ทั้งสองตัวแยกกันได้

## Hardware

- Arduino UNO
- Laser Transmitter x2
- Laser Receiver x2

## Pin Configuration

### Laser Sensor 1

| Pin | Device |
|---|---|
| D9 | Laser TX 1 |
| D10 | Laser RX 1 |

### Laser Sensor 2

| Pin | Device |
|---|---|
| D11 | Laser TX 2 |
| D12 | Laser RX 2 |

## System Diagram

```text
Laser TX 1
    |
    | Laser Beam 1
    v
Laser RX 1
    |
    v
Arduino D10


Laser TX 2
    |
    | Laser Beam 2
    v
Laser RX 2
    |
    v
Arduino D12
```

## Expected Logic

| Receiver | State |
|---|---|
| HIGH | LASER DETECTED |
| LOW | LASER LOST |

## Test 1

Laser ทั้งสองตัวตรวจพบ

```
Laser 1 = 1 DETECTED    |    Laser 2 = 1 DETECTED
```

## Test 2

บัง Laser 1

```
Laser 1 = 0 LOST        |    Laser 2 = 1 DETECTED
```

Laser 2 ต้องยังตรวจพบได้

## Test 3

บัง Laser 2

```
Laser 1 = 1 DETECTED    |    Laser 2 = 0 LOST
```

Laser 1 ต้องยังตรวจพบได้

## Test 4

บัง Laser ทั้งสอง

```
Laser 1 = 0 LOST        |    Laser 2 = 0 LOST
```

## Serial Monitor

Baud Rate

```
9600
```

## Expected Result

Laser ทั้งสองชุดต้องสามารถอ่านค่าแยกกันได้

การบัง Laser 1 ต้องไม่ทำให้ Laser 2 เปลี่ยนสถานะ

การบัง Laser 2 ต้องไม่ทำให้ Laser 1 เปลี่ยนสถานะ

## Result

- [ ] Laser 1 ทำงาน
- [ ] Laser 2 ทำงาน
- [ ] Laser 1 อ่านค่าได้ถูกต้อง
- [ ] Laser 2 อ่านค่าได้ถูกต้อง
- [ ] Sensor ทั้งสองทำงานพร้อมกัน
- [ ] Sensor ไม่รบกวนกัน
