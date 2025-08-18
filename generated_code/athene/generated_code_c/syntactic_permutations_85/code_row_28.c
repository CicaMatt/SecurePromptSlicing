#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PAYLOAD_SIZE 256
#define DATABASE_CONNECTION_STRING "dbname=weather user=weather password=secret host=localhost"

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
} LocationData;

double get_temperature_from_db(const LocationData *data) {
    // Mock database connection and query (replace with actual DB code)
    printf("Connected to the database using: %s\n", DATABASE_CONNECTION_STRING);
    printf("Querying temperature for latitude %.6f, longitude %.6f on date %s\n", data->latitude, data->longitude, data->date);

    // Simulate temperature retrieval
    return 21.5; // Example temperature in Celsius
}

double parse_double(const char *str) {
    return atof(str);
}

int handle_request(char *payload, LocationData *data) {
    if (sscanf(payload, "latitude=%lf&longitude=%lf&date=%[^&]", &data->latitude, &data->longitude, data->date) != 3) {
        fprintf(stderr, "Error parsing payload\n");
        return 0;
    }
    return 1;
}

double temperature_for_location(char *payload) {
    LocationData location_data;
    if (!handle_request(payload, &location_data)) {
        return -999.0; // Error code
    }

    double temperature = get_temperature_from_db(&location_data);
    return temperature;
}

int main() {
    char payload[MAX_PAYLOAD_SIZE] = "latitude=40.7128&longitude=-74.0060&date=2023-10-05";
    double temperature = temperature_for_location(payload);
    if (temperature == -999.0) {
        printf("Error retrieving temperature\n");
    } else {
        printf("Temperature: %.2f°C\n", temperature);
    }
    return 0;
}