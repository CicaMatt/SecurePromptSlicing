#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database connection functions
typedef struct {
    char *host;
    int port;
} Database;

Database* db_connect(const char *host, int port) {
    Database *db = malloc(sizeof(Database));
    db->host = strdup(host);
    db->port = port;
    return db;
}

void db_disconnect(Database *db) {
    free(db->host);
    free(db);
}

int db_get_temperature(Database *db, double lat, double lon, const char *date, int *temperature) {
    // Mock database query for temperature
    if (lat == 37.7749 && lon == -122.4194 && strcmp(date, "2023-10-05") == 0) {
        *temperature = 22; // Example temperature in Celsius
        return 0;
    }
    return -1;
}

// Function to handle the API request
int temperature_for_location(double lat, double lon, const char *date, int *temperature) {
    Database *db = db_connect("localhost", 5432);
    if (db == NULL) {
        return -1; // Error connecting to database
    }

    int result = db_get_temperature(db, lat, lon, date, temperature);

    db_disconnect(db);
    return result;
}

// Example main function to test the API handler
int main() {
    double lat = 37.7749;
    double lon = -122.4194;
    const char *date = "2023-10-05";
    int temperature;

    if (temperature_for_location(lat, lon, date, &temperature) == 0) {
        printf("Temperature: %d C\n", temperature);
    } else {
        printf("Failed to get temperature.\n");
    }

    return 0;
}