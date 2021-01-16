// DHTlib
// https://github.com/RobTillaart/DHTlib
#include <dht.h>

// Node name
#define NAME "A1"

// Sensor DHT22
dht DHT22;
#define DHT22PIN 2

// Buffer for serialized data
char buff[260];

// Time of last sensor update
unsigned long lastSensorUpdate = 0;

void setup()
{
    // Setup serial for communication with Xbee
    Serial.begin(9600); 
}

void loop()
{
    // Read sensor every five seconds
    if (millis() - lastSensorUpdate >= 5 * 1000UL)
    {
        // Next update
        lastSensorUpdate = millis();
        
        // Read sensor data as JSON
        readSensor(buff);
        
        // Send sensor data to database
        sendData(0x1, buff, strlen(buff));
    }
}

void readSensor(char *buff)
{
    // Return "ping" instead of data to differentiate
    // Arduino failure form sensor failure
    if(DHTLIB_OK != DHT22.read(DHT22PIN)) {
        sprintf(buff, "{\"name\": \"%s\"}", NAME);
        return;
    }

    // Return sensor data
    sprintf(
        buff,
        "{\"name\": \"%s\",\"humidity\": %d.%02d,\"temperature\": %d.%02d}",
        NAME,
        (int)DHT22.humidity, (int)(DHT22.humidity * 100) % 100,
        (int)DHT22.temperature, (int)(DHT22.temperature * 100) % 100);
}

bool sendData(uint16_t destination, const char *data, size_t size)
{
    // Max data size
    if (size > 256)
        return false;

    char *frame = new char[9 + size];

    // Start delimiter
    frame[0] = 0x7E;

    // Frame size (big endian)
    frame[1] = (size + 5) >> 8;
    frame[2] = (size + 5) & 0xFF;

    // Frame type
    frame[3] = 0x01;

    // Frame ID
    frame[4] = 0x01;

    // Destination (big endian) TODO
    frame[5] = destination >> 8;
    frame[6] = destination & 0xFF;

    // Options
    frame[7] = 0x00;

    // RF data
    for (size_t i = 0; i < size; i++)
    {
        frame[8 + i] = data[i];
    }

    // Checksum
    frame[8 + size] = 0x00;

    for (size_t i = 3; i < 8 + size; i++)
    {
        frame[8 + size] += frame[i];
    }

    frame[8 + size] = 0xFF - frame[8 + size];

    // Send frame
    Serial.write(frame, 9 + size);

    delete[] frame;

    return true;
}
