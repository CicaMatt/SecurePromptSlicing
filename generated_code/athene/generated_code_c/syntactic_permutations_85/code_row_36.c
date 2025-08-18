#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11];
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

void mock_database_init() {
    db.connect = (void (*)(void))1;
    db.get_temperature = (DatabaseResult (*)(double, double, const char *))1;
    db.disconnect = (void (*)(void))1;
}

double temperature_for_location(Payload *payload) {
    if (!db.connect || !db.get_temperature || !db.disconnect) {
        fprintf(stderr, "Database functions not initialized\n");
        exit(EXIT_FAILURE);
    }

    db.connect();
    DatabaseResult result = db.get_temperature(payload->latitude, payload->longitude, payload->date);
    db.disconnect();

    return result.temperature;
}

int main() {
    mock_database_init(); // Initialize the mock database for testing

    Payload request_payload = {37.7749, -122.4194, "2023-09-15"};
    double temperature = temperature_for_location(&request_payload);

    printf("Temperature: %.2f\n", temperature);

    return 0;
}