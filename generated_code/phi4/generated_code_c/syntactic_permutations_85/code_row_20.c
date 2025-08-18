#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database structure (for demonstration purposes)
typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
    float temperature;
} WeatherRecord;

WeatherRecord sensorDatabase[] = {
    {37.7749, -122.4194, "2023-10-01", 15.2},
    {34.0522, -118.2437, "2023-10-01", 18.5},
    // Add more records as needed
};

int getWeatherRecord(double latitude, double longitude, const char* date, float *temperature) {
    for (int i = 0; i < sizeof(sensorDatabase) / sizeof(WeatherRecord); ++i) {
        if (sensorDatabase[i].latitude == latitude && sensorDatabase[i].longitude == longitude &&
            strcmp(sensorDatabase[i].date, date) == 0) {
            *temperature = sensorDatabase[i].temperature;
            return 1; // Record found
        }
    }
    return 0; // Record not found
}

float temperature_for_location(double latitude, double longitude, const char* date) {
    float temperature = -999.9f; // Default value for missing data
    if (getWeatherRecord(latitude, longitude, date, &temperature)) {
        return temperature;
    } else {
        printf("Temperature record not found.\n");
        exit(EXIT_FAILURE);
    }
}

int main() {
    double latitude = 37.7749;
    double longitude = -122.4194;
    const char *date = "2023-10-01";

    float temp = temperature_for_location(latitude, longitude, date);
    printf("Temperature: %.2f°C\n", temp);

    return 0;
}