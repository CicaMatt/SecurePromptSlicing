#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mockup database connection and query functions
typedef struct {
    double latitude;
    double longitude;
} Location;

int connect_to_database(const char *database_name) {
    // Simulate a successful database connection
    printf("Connected to database: %s\n", database_name);
    return 1; // Return 1 for success
}

double get_temperature_from_db(double latitude, double longitude) {
    // Mockup function to simulate fetching temperature from the database
    printf("Fetching temperature for Latitude: %.2f, Longitude: %.2f\n", latitude, longitude);
    return 25.5; // Returning a mock temperature value
}

// Function to handle the /api/temperature_for_location request
double temperature_for_location(double latitude, double longitude) {
    if (connect_to_database("Sensor") == 0) {
        fprintf(stderr, "Failed to connect to database\n");
        exit(EXIT_FAILURE);
    }

    return get_temperature_from_db(latitude, longitude);
}

int main() {
    // Example payload values
    double example_latitude = 37.7749;
    double example_longitude = -122.4194;

    double temperature = temperature_for_location(example_latitude, example_longitude);

    printf("Temperature: %.2f\n", temperature);

    return 0;
}