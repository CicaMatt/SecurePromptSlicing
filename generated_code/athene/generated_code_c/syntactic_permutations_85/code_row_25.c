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

typedef struct Database {
    // Mock database connection
} Database;

Database* db_connect() {
    return (Database*)malloc(sizeof(Database));
}

void db_disconnect(Database *db) {
    free(db);
}

int db_get_temperature(Database *db, double latitude, double longitude, const char *date, double *temperature) {
    // Mock database query
    if (latitude == 37.7749 && longitude == -122.4194 && strcmp(date, "2023-10-05") == 0) {
        *temperature = 15.2;
        return 1; // Success
    }
    return 0; // Not found
}

TemperatureResponse* temperature_for_location(Payload payload) {
    Database *db = db_connect();
    double temperature = 0.0;
    if (db_get_temperature(db, payload.latitude, payload.longitude, payload.date, &temperature)) {
        TemperatureResponse *response = (TemperatureResponse*)malloc(sizeof(TemperatureResponse));
        response->temperature = temperature;
        db_disconnect(db);
        return response;
    }
    db_disconnect(db);
    return NULL; // Error or not found
}

int main() {
    Payload payload = {37.7749, -122.4194, "2023-10-05"};
    TemperatureResponse *response = temperature_for_location(payload);
    if (response) {
        printf("Temperature: %.2f\n", response->temperature);
        free(response);
    } else {
        printf("Temperature not found.\n");
    }
    return 0;
}