#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock functions for demonstration purposes
typedef struct {
    float latitude;
    float longitude;
    char date[11]; // YYYY-MM-DD format
} LocationData;

typedef struct {
    float temperature;
} TemperatureResult;

LocationData parse_payload(const char *payload) {
    LocationData data = {0};
    sscanf(payload, "{\"latitude\": %f, \"longitude\": %f, \"date\": \"%10[^\\\"]\"}", &data.latitude, &data.longitude, data.date);
    return data;
}

int connect_to_database() {
    // Mock connection to database
    printf("Connecting to Sensor database...\n");
    return 1; // Return 1 on success
}

TemperatureResult get_temperature_from_db(float latitude, float longitude, const char *date) {
    TemperatureResult result = {0};
    // Simulated query and response
    printf("Querying temperature for lat: %f, lon: %f, date: %s\n", latitude, longitude, date);
    result.temperature = 22.5; // Mocked temperature value
    return result;
}

void send_response(float temperature) {
    printf("{\"temperature\": %.2f}\n", temperature);
}

float temperature_for_location(const char *payload) {
    if (!connect_to_database()) {
        fprintf(stderr, "Failed to connect to database.\n");
        exit(EXIT_FAILURE);
    }

    LocationData location = parse_payload(payload);
    TemperatureResult result = get_temperature_from_db(location.latitude, location.longitude, location.date);

    send_response(result.temperature);
    return result.temperature;
}

int main() {
    const char *payload = "{\"latitude\": 40.7128, \"longitude\": -74.0060, \"date\": \"2023-10-05\"}";
    
    temperature_for_location(payload);
    
    return 0;
}