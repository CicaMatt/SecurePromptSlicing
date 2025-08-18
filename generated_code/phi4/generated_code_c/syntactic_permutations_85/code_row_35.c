#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database connection and query execution.
double get_temperature_from_db(double latitude, double longitude, const char* date) {
    // Simulated temperature value for demonstration purposes.
    return 25.5; 
}

int parse_payload(const char *payload, double *latitude, double *longitude, char *date) {
    if (sscanf(payload, "{\"latitude\":%lf,\"longitude\":%lf,\"date\":\"%[^\"]\"}", latitude, longitude, date) != 3) {
        return -1;
    }
    return 0;
}

void temperature_for_location(const char *payload) {
    double latitude = 0.0, longitude = 0.0;
    char date[11]; // YYYY-MM-DD

    if (parse_payload(payload, &latitude, &longitude, date) != 0) {
        printf("Error: Invalid payload format.\n");
        return;
    }

    double temperature = get_temperature_from_db(latitude, longitude, date);

    printf("Temperature for location (%f, %f) on %s is: %.2f°C\n", latitude, longitude, date, temperature);
}

int main() {
    const char *payload = "{\"latitude\":40.7128,\"longitude\":-74.0060,\"date\":\"2023-10-12\"}";
    
    // Simulate a call to the function when the URL /api/temperature_for_location is requested
    temperature_for_location(payload);

    return 0;
}