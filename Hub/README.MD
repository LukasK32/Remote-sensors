# Hub

Example hub code for Raspberry PI with InfluxDB.

## Pinout

XBee is expected on serial port (`/dev/ttyS0`; must be enabled in `raspi-config` with inaccessible shell).

## XBee configuration

| Parameter                | Value  |
| ------------------------ | ------ |
| Node Identifier          | RPi    |
| Channel                  | 0x18   |
| PAN ID                   | 4813   |
| Destination address high | 0      |
| Destination address low  | 0xFFFF |
| Address                  | 0x1    |
| Coordinator enable       | True   |
| API Enable               | False  |