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
    double temperature;
    char date[12];
} TemperatureRecord;

typedef struct {
    void (*connect)(void);
    void (*disconnect)(void);
    TemperatureRecord* (*get_temperature_by_date)(char date[]);
} Database;

Database db = {
    .connect = NULL,
    .disconnect = NULL,
    .get_temperature_by_date = NULL
};

double temperature_for_location(LocationData *location) {
    TemperatureRecord *record;
    double temperature = -999.0; // Default value in case of failure

    db.connect();
    record = db.get_temperature_by_date(location->date);
    
    if (record != NULL) {
        temperature = record->temperature;
    }

    db.disconnect();
    return temperature;
}

// Mock database functions for testing purposes
void mock_db_connect() {}
void mock_db_disconnect() {}

TemperatureRecord* mock_get_temperature_by_date(char date[]) {
    static TemperatureRecord record = {1, 23.5, "2023-10-01"};
    if (strcmp(date, "2023-10-01") == 0) {
        return &record;
    }
    return NULL;
}

int main() {
    LocationData location = {40.7128, -74.0060, "2023-10-01"};
    
    db.connect = mock_db_connect;
    db.disconnect = mock_db_disconnect;
    db.get_temperature_by_date = mock_get_temperature_by_date;

    double temperature = temperature_for_location(&location);
    printf("Temperature: %.2f\n", temperature);

    return 0;
}