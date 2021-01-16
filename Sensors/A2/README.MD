# BME280 Sensor

Example sensor code for Arduino Mega with BME280.

## Pinout

| Arduino PIN  | BME280 PIN |
| ------------ | ---------- |
| 20 (SDA)     | SDA        |
| 21 (SCL)     | SCL        |
| 3.3V         | VCC        |
| GND          | GND        |

XBee is expected on UART (Serial).

## XBee configuration

| Parameter                | Value |
| ------------------------ | ----- |
| Node Identifier          | A2    |
| Channel                  | 0x18  |
| PAN ID                   | 4813  |
| Destination address high | 0     |
| Destination address low  | 0x1   |
| Address                  | 0x3   |
| Coordinator enable       | False |
| API Enable               | True  |