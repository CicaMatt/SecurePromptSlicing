#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    double lat;
    double lon;
    char date[11];
} LocationRequest;

double execute_query(double lat, double lon, const char *date) {
    // Simulate a database query or API call to get temperature
    // This is a placeholder function; actual implementation will vary
    return 22.5; // Example temperature in Celsius
}

double temperature_for_location(LocationRequest *request) {
    double lat = request->lat;
    double lon = request->lon;
    char date[11];
    strncpy(date, request->date, sizeof(date) - 1);
    date[sizeof(date) - 1] = '\0';

    return execute_query(lat, lon, date);
}

int main() {
    LocationRequest request = {37.7749, -122.4194, "2023-10-01"};
    double temperature = temperature_for_location(&request);
    printf("Temperature: %.2f\n", temperature);
    return 0;
}