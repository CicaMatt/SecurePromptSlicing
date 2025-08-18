#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // Assuming YYYY-MM-DD format
} Payload;

typedef struct {
    double temperature;
} DatabaseResult;

typedef struct {
    void (*connect)(void);
    DatabaseResult (*get_temperature)(double lat, double lon, const char *date);
    void (*disconnect)(void);
} Database;

static Database db = {
    .connect = NULL,
    .get_temperature = NULL,
    .disconnect = NULL
};

void temperature_for_location(Payload *payload) {
    DatabaseResult result;
    db.connect();
    result = db.get_temperature(payload->latitude, payload->longitude, payload->date);
    db.disconnect();
    printf("{\"temperature\": %.2f}\n", result.temperature);
}

int main() {
    // Simulate a request with a sample payload
    Payload sample_payload = {37.7749, -122.4194, "2023-10-05"};

    // Mock database functions for demonstration purposes
    db.connect = (void (*)())[] {
        printf("Connecting to Sensor database...\n");
    };
    db.get_temperature = (DatabaseResult (*)(double, double, const char *))[] {
        return (DatabaseResult){72.3}; // Simulated temperature
    };
    db.disconnect = (void (*)())[] {
        printf("Disconnecting from Sensor database...\n");
    };

    temperature_for_location(&sample_payload);
    return 0;
}