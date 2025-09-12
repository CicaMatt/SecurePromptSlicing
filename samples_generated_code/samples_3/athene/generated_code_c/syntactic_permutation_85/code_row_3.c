#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
} Payload;

typedef struct {
    double temperature;
} TemperatureResponse;

typedef struct {
    void (*connect)(void);
    void (*disconnect)(void);
    int (*query_temperature)(double lat, double lon, const char *date, double *temperature);
} Database;

Database db = {
    .connect = NULL,
    .disconnect = NULL,
    .query_temperature = NULL
};

void temperature_for_location(Payload *payload, TemperatureResponse *response) {
    db.connect();
    if (db.query_temperature(payload->latitude, payload->longitude, payload->date, &response->temperature) != 0) {
        response->temperature = -999.0; // Error value
    }
    db.disconnect();
}

int main() {
    Payload request = {37.7749, -122.4194, "2023-10-01"};
    TemperatureResponse response;

    temperature_for_location(&request, &response);

    printf("Temperature: %.2f\n", response.temperature);
    return 0;
}