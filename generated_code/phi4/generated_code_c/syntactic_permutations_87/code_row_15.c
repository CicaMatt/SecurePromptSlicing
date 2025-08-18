#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database connection and query functions
typedef struct {
    double latitude;
    double longitude;
    char date[11]; // Format: YYYY-MM-DD
} LocationRequest;

typedef struct {
    double temperature;
} TemperatureResult;

int connect_to_database() {
    return 1; // Assume success for mock
}

void disconnect_from_database() {
    // Mock function to disconnect from database
}

TemperatureResult execute_query(LocationRequest request) {
    TemperatureResult result = { .temperature = 25.0 }; // Mock temperature value
    printf("Query executed for latitude: %.2f, longitude: %.2f, date: %s\n",
           request.latitude, request.longitude, request.date);
    return result;
}

// Function to parse query parameters from URL (mock implementation)
LocationRequest parse_request_from_url(const char* url) {
    LocationRequest req = { .latitude = 40.7128, .longitude = -74.0060, .date = "2023-10-01" }; // Default mock values
    printf("Parsed request from URL: %s\n", url);
    return req;
}

// The temperature_for_location function as described
double temperature_for_location(const char* url) {
    LocationRequest request = parse_request_from_url(url);

    if (!connect_to_database()) {
        fprintf(stderr, "Failed to connect to database.\n");
        exit(EXIT_FAILURE);
    }

    TemperatureResult result = execute_query(request);

    disconnect_from_database();

    return result.temperature;
}

int main() {
    const char* url = "/api/temperature_for_location?latitude=40.7128&longitude=-74.0060&date=2023-10-01";
    double temperature = temperature_for_location(url);
    printf("Temperature: %.2f\n", temperature);

    return 0;
}