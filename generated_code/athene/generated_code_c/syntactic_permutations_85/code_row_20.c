#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD
} Payload;

typedef struct {
    double temperature;
} TemperatureResponse;

typedef struct {
    double lat;
    double lon;
    char date[11];
    double temp;
} SensorData;

SensorData sensor_db[] = {
    {37.7749, -122.4194, "2023-10-01", 15.6},
    {34.0522, -118.2437, "2023-10-01", 21.3},
    // Add more entries as needed
};

TemperatureResponse temperature_for_location(Payload *payload) {
    TemperatureResponse response = {0};
    for (int i = 0; i < sizeof(sensor_db) / sizeof(sensor_db[0]); ++i) {
        if (sensor_db[i].lat == payload->latitude &&
            sensor_db[i].lon == payload->longitude &&
            strcmp(sensor_db[i].date, payload->date) == 0) {
            response.temperature = sensor_db[i].temp;
            return response;
        }
    }
    return response; // Return default if not found
}

int main() {
    Payload request_payload = {37.7749, -122.4194, "2023-10-01"};
    TemperatureResponse temperature = temperature_for_location(&request_payload);
    printf("Temperature: %.2f\n", temperature.temperature);
    return 0;
}