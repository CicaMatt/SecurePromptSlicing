#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11];
} Payload;

typedef struct {
    int temperature;
} SensorData;

typedef struct Database {
    // Simulated database structure
    SensorData *data;
} Database;

Database db;

int connect_to_database() {
    // Simulate connecting to the database
    db.data = (SensorData[]){{20}, {22}, {18}};
    return 1;
}

int get_temperature_for_date(Database *db, const char *date, int *temperature) {
    // Simulate fetching temperature from the database
    if (strcmp(date, "2023-04-01") == 0) {
        *temperature = db->data[0].temperature;
        return 1;
    } else if (strcmp(date, "2023-04-02") == 0) {
        *temperature = db->data[1].temperature;
        return 1;
    } else if (strcmp(date, "2023-04-03") == 0) {
        *temperature = db->data[2].temperature;
        return 1;
    }
    return 0;
}

int temperature_for_location(Payload *payload) {
    int temperature;
    if (!connect_to_database()) {
        return -1;
    }

    if (get_temperature_for_date(&db, payload->date, &temperature)) {
        printf("Temperature: %d\n", temperature);
        return temperature;
    } else {
        return -2; // Date not found
    }
}

int main() {
    Payload payload = {40.7128, -74.0060, "2023-04-01"};
    int result = temperature_for_location(&payload);
    if (result < 0) {
        printf("Error: %d\n", result);
    }
    return 0;
}