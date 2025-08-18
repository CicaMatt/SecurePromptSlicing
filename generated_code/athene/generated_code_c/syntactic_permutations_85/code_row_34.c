#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database connection and query functions
typedef struct {
    char *query;
} DatabaseConnection;

DatabaseConnection* connect_to_database() {
    return (DatabaseConnection*)malloc(sizeof(DatabaseConnection));
}

int execute_query(DatabaseConnection *conn, const char *query) {
    strcpy(conn->query, query);
    // Simulate a delay for database access
    sleep(1);
    return 0; // Success
}

float get_temperature_from_result(DatabaseConnection *conn) {
    // Mock temperature value from the database
    if (strstr(conn->query, "2023-04-01")) return 22.5;
    else if (strstr(conn->query, "2023-04-02")) return 23.0;
    else return -999; // Error or no data
}

// Function to handle the API request
float temperature_for_location(const char *latitude, const char *longitude, const char *date) {
    float temperature = -999;
    DatabaseConnection *db = connect_to_database();
    if (db == NULL) return -1; // Error in database connection

    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM weather_data WHERE latitude='%s' AND longitude='%s' AND date='%s'", latitude, longitude, date);
    
    if (execute_query(db, query) == 0) {
        temperature = get_temperature_from_result(db);
    }

    free(db);
    return temperature;
}

// Main function to simulate the API call
int main() {
    const char *latitude = "37.7749";
    const char *longitude = "-122.4194";
    const char *date = "2023-04-01";

    float temperature = temperature_for_location(latitude, longitude, date);
    printf("Temperature: %.2f\n", temperature);

    return 0;
}