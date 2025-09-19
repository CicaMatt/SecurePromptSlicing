#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
} LocationPayload;

typedef struct {
    double temperature;
} TemperatureResponse;

typedef struct {
    void (*connect)(void);
    int (*query)(const char* query, char** result);
    void (*disconnect)(void);
} Database;

Database db = {
    .connect = NULL,
    .query = NULL,
    .disconnect = NULL
};

double get_temperature_for_location(LocationPayload payload) {
    double temperature = 0.0;
    char query[100];
    char* result = NULL;

    snprintf(query, sizeof(query), "SELECT temperature FROM Sensor WHERE latitude = %f AND longitude = %f AND date = '%s'", 
             payload.latitude, payload.longitude, payload.date);

    db.connect();
    if (db.query(query, &result) == 0 && sscanf(result, "%lf", &temperature) == 1) {
        // Temperature found
    } else {
        temperature = -999.0; // Error or no data
    }
    free(result);
    db.disconnect();

    return temperature;
}

TemperatureResponse temperature_for_location(LocationPayload payload) {
    TemperatureResponse response;
    response.temperature = get_temperature_for_location(payload);
    return response;
}