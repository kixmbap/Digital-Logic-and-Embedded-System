# Laser Test

โปรแกรมสำหรับทดสอบ Laser Transmitter และ Laser Receiver จำนวน 1 ชุด

## Objective

ตรวจสอบว่า Laser Transmitter สามารถส่งลำแสงไปยัง Laser Receiver ได้ และตรวจสอบค่า HIGH/LOW ของ Receiver

## Hardware

- Arduino UNO
- Laser Transmitter
- Laser Receiver
- Jumper Wire

## Pin Configuration

### Laser Transmitter

| Arduino Pin | Device |
|---|---|
| D9 | Laser TX |
| 5V | VCC |
| GND | GND |

### Laser Receiver

| Arduino Pin | Device |
|---|---|
| D10 | Laser RX |
| 5V | VCC |
| GND | GND |

## Wiring

```text
Laser TX
   |
   | Laser Beam
   |
   v
Laser RX
```

ต้องจัด Laser TX ให้ยิงตรงกับ Laser RX

## Expected Logic

โปรแกรมเบื้องต้นกำหนดว่า

| Receiver | Meaning |
|---|---|
| HIGH | LASER DETECTED |
| LOW | LASER LOST |

แต่ควรตรวจสอบค่าจริงของ Sensor ก่อนนำไปใช้กับระบบ Final

## Test 1: Laser Detected

จัด Laser TX และ Laser RX ให้ตรงกัน

```
TX --------------------> RX
```

Serial Monitor ควรแสดง

```
RX VALUE = 1 -> LASER DETECTED
```

## Test 2: Laser Lost

ใช้มือหรือวัตถุบังลำแสง

```
TX -------- X ---------> RX
```

Serial Monitor ควรเปลี่ยนเป็น

```
RX VALUE = 0 -> LASER LOST
```

## Important

หาก Sensor ของคุณให้ค่ากลับกัน เช่น

```
Laser Detected = LOW
Laser Lost = HIGH
```

ต้องเปลี่ยน Logic ในโปรแกรม Final ให้ตรงกับ Sensor จริง

## Result

- [ ] Laser TX ทำงาน
- [ ] Laser RX อ่านค่าได้
- [ ] ตรวจพบ Laser ได้
- [ ] ตรวจพบเมื่อ Laser ถูกบัง
- [ ] ทราบค่า HIGH/LOW ที่ถูกต้อง
