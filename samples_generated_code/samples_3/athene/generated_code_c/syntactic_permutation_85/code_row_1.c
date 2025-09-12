#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
} Payload;

typedef struct {
    double temperature;
} TemperatureResponse;

typedef struct {
    void (*connect)(void);
    int (*query)(const char*, char*);
    void (*disconnect)(void);
} Database;

Database db = {
    .connect = NULL,
    .query = NULL,
    .disconnect = NULL
};

void init_database() {
    // Initialize the database connection functions
    // This is a placeholder for actual initialization code
}

double get_temperature_from_db(const char* query) {
    char result[100];
    double temperature;
    if (db.query(query, result)) {
        sscanf(result, "%lf", &temperature);
    } else {
        temperature = -999.0; // Error value
    }
    return temperature;
}

TemperatureResponse temperature_for_location(Payload* payload) {
    init_database();
    db.connect();

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM Sensor WHERE latitude=%lf AND longitude=%lf AND date='%s'", 
             payload->latitude, payload->longitude, payload->date);

    double temperature = get_temperature_from_db(query);
    
    TemperatureResponse response = { .temperature = temperature };
    db.disconnect();
    return response;
}

int main() {
    // Example usage
    Payload payload = { 37.7749, -122.4194, "2023-01-01" };
    TemperatureResponse response = temperature_for_location(&payload);
    printf("Temperature: %.2f\n", response.temperature);
    return 0;
}