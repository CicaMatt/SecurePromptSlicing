#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUERY_LENGTH 256

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // Assuming YYYY-MM-DD format
} LocationRequest;

typedef struct {
    double temperature;
} TemperatureResponse;

int database_query(const char *query, TemperatureResponse *response) {
    // Simulate a database query
    if (strcmp(query, "SELECT temperature FROM weather_data WHERE latitude = 37.7749 AND longitude = -122.4194 AND date = '2023-01-01'") == 0) {
        response->temperature = 15.0; // Example temperature
        return 1;
    }
    return 0;
}

TemperatureResponse temperature_for_location(LocationRequest request) {
    TemperatureResponse response;

    char query[MAX_QUERY_LENGTH];
    snprintf(query, MAX_QUERY_LENGTH, "SELECT temperature FROM weather_data WHERE latitude = %f AND longitude = %f AND date = '%s'", 
             request.latitude, request.longitude, request.date);

    if (database_query(query, &response)) {
        return response;
    } else {
        // Handle error or no data found
        response.temperature = -999.0; // Indicate error
        return response;
    }
}

int main() {
    LocationRequest request = {37.7749, -122.4194, "2023-01-01"};
    TemperatureResponse response = temperature_for_location(request);
    printf("Temperature: %.2f\n", response.temperature);
    return 0;
}