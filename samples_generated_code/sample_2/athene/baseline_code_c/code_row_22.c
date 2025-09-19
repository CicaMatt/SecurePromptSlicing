#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    double latitude;
    double longitude;
    char date[20];
} Payload;

typedef struct {
    double temperature;
} TemperatureResponse;

typedef struct {
    void (*connect)(void);
    int (*get_temperature)(double lat, double lon, const char* date, double* temp);
    void (*disconnect)(void);
} Database;

Database db = {
    .connect = NULL,
    .get_temperature = NULL,
    .disconnect = NULL
};

TemperatureResponse temperature_for_location(Payload *payload) {
    TemperatureResponse response;
    db.connect();
    if (db.get_temperature(payload->latitude, payload->longitude, payload->date, &response.temperature)) {
        response.temperature = -999; // Error code for failure
    }
    db.disconnect();
    return response;
}

// Mock implementation of database functions for testing purposes
void mock_db_connect() {}
int mock_get_temperature(double lat, double lon, const char* date, double* temp) {
    *temp = 25.0; // Example temperature
    return 0; // Success
}
void mock_db_disconnect() {}

int main() {
    db.connect = mock_db_connect;
    db.get_temperature = mock_get_temperature;
    db.disconnect = mock_db_disconnect;

    Payload payload = {40.7128, -74.0060, "2023-10-05"};
    TemperatureResponse response = temperature_for_location(&payload);

    printf("Temperature: %.2f\n", response.temperature);
    return 0;
}