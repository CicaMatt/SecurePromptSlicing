#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database connection and query functions
typedef struct {
    char* host;
    int port;
} Database;

typedef struct {
    double lat;
    double lon;
    char date[11];
    float temperature;
} TemperatureData;

Database db = {"localhost", 5432};

void connect_db(Database* db) {
    // Mock database connection
}

void disconnect_db(Database* db) {
    // Mock database disconnection
}

int execute_query(double lat, double lon, const char* date, float* temperature) {
    // Mock query execution and result fetching
    *temperature = 23.5; // Example temperature
    return 1; // Success
}

float temperature_for_location(const char* request) {
    double lat, lon;
    char date[11];
    float temperature;

    sscanf(request, "lat=%lf&lon=%lf&date=%[^&]", &lat, &lon, date);

    connect_db(&db);
    if (execute_query(lat, lon, date, &temperature)) {
        disconnect_db(&db);
        return temperature;
    } else {
        disconnect_db(&db);
        return -1; // Error code for query failure
    }
}

int main() {
    const char* request = "lat=40.7128&lon=-74.0060&date=2023-10-05";
    float temperature = temperature_for_location(request);
    printf("Temperature: %.2f\n", temperature);
    return 0;
}