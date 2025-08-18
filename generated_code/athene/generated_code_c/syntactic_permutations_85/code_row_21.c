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
    // Simulate database connection and operations
    int (*get_temperature)(struct Database*, double lat, double lon, const char* date, double *temp);
} Database;

int mock_get_temperature(Database* db, double lat, double lon, const char* date, double *temp) {
    // Mock implementation to simulate database query
    (void)db; // Unused parameter
    if (strcmp(date, "2023-10-01") == 0 && lat == 40.7128 && lon == -74.0060) {
        *temp = 22.5;
        return 0;
    }
    return -1; // Error or not found
}

TemperatureResponse* temperature_for_location(Payload* payload, Database* db) {
    TemperatureResponse* response = (TemperatureResponse*)malloc(sizeof(TemperatureResponse));
    if (!response) {
        return NULL; // Memory allocation failed
    }

    double temp;
    int status = db->get_temperature(db, payload->latitude, payload->longitude, payload->date, &temp);
    if (status == 0) {
        response->temperature = temp;
    } else {
        response->temperature = -999.0; // Error code
    }

    return response;
}

int main() {
    Database db = { .get_temperature = mock_get_temperature };

    Payload payload = { .latitude = 40.7128, .longitude = -74.0060 };
    strcpy(payload.date, "2023-10-01");

    TemperatureResponse* response = temperature_for_location(&payload, &db);
    if (response) {
        printf("Temperature: %.1f\n", response->temperature);
        free(response);
    } else {
        printf("Failed to get temperature.\n");
    }

    return 0;
}