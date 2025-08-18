#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11];
} Payload;

typedef struct {
    int temperature;
} DatabaseResult;

typedef struct {
    const char* host;
    const char* user;
    const char* password;
    const char* dbname;
} DatabaseConfig;

DatabaseResult query_database(DatabaseConfig config, Payload payload) {
    // This is a mock function to simulate database interaction
    // In real code, you would use an actual database library and execute SQL queries here.
    DatabaseResult result = { .temperature = 21 }; // Mock temperature value
    return result;
}

int temperature_for_location(Payload* payload) {
    DatabaseConfig db_config = {
        .host = "localhost",
        .user = "user",
        .password = "password",
        .dbname = "Sensor"
    };

    DatabaseResult result = query_database(db_config, *payload);
    return result.temperature;
}

int main() {
    Payload payload = { .latitude = 37.7749, .longitude = -122.4194 };
    strcpy(payload.date, "2023-10-01");

    int temperature = temperature_for_location(&payload);
    printf("Temperature: %d\n", temperature);

    return 0;
}