# DHT22 Sensor

Example sensor code for Arduino Mega with DHT22.

## Pinout

| Arduino PIN  | DHT22 PIN              |
| ------------ | ---------------------- |
| 2            | Data (PULL UP to VCC)  |
| 5V           | VCC                    |
| GND          | GND                    |

XBee is expected on UART (Serial).

## XBee configuration

| Parameter                | Value |
| ------------------------ | ----- |
| Node Identifier          | A1    |
| Channel                  | 0x18  |
| PAN ID                   | 4813  |
| Destination address high | 0     |
| Destination address low  | 0x1   |
| Address                  | 0x2   |
| Coordinator enable       | False |
| API Enable               | True  |