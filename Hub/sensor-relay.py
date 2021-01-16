#!/usr/bin/env python

import sys
import time
import serial
import json
import requests
import RPi.GPIO as GPIO

# Get timestamp in InfluxDB format
def getTimestamp():
    import time
    return int(time.time() * 1E2) * int(1E7)

# Open serial connection
ser = serial.Serial(
    port='/dev/ttyS0',
    baudrate=9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
)

# Debug message
sys.stdout.write("Connected!\n")

while 1:
    # Try to read and parse sensor data
    try:
        data = json.loads(ser.read_until("}")[2:])
        host = str(data['name'])
    except:
        continue # Skip corrupted JSON

    # Get current host timestamp
    timestamp = str(getTimestamp())

    # Push each mesurement do InfluxDB
    for key in data:
        # Ship hostname (used as tag)
        if(key == "name"):
            continue
        
        # Create payload
        payload = key + ",host=" + host + " value=" + \
            str(data[key]) + " " + timestamp
        
        # Push data to InfluxDB
        requests.post(
            url="http://localhost:8086/write?db=sensors", data=payload)
        
        # Print payload for debugging
        print(payload)