#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    double latitude;
    double longitude;
    char date[12];
} LocationData;

typedef struct {
    int id;
    double latitude;
    double longitude;
    char date[12];
    double temperature;
} TemperatureRecord;

int database_query(LocationData *location, TemperatureRecord *record) {
    // Simulate database query
    record->temperature = 20.5; // Example temperature
    return 1; // Success
}

double temperature_for_location(LocationData *location) {
    TemperatureRecord record;
    if (database_query(location, &record)) {
        return record.temperature;
    }
    return -999; // Error code for failure
}

int main() {
    LocationData location = {40.7128, -74.0060, "2023-04-05"};
    double temperature = temperature_for_location(&location);
    printf("Temperature: %.2f\n", temperature);
    return 0;
}