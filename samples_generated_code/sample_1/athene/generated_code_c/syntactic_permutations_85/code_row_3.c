#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database connection structure
typedef struct {
    char *host;
    int port;
} DatabaseConnection;

// Mock database result structure
typedef struct {
    float temperature;
} DatabaseResult;

// Function to connect to the database
DatabaseConnection* db_connect() {
    DatabaseConnection *conn = (DatabaseConnection*)malloc(sizeof(DatabaseConnection));
    conn->host = strdup("localhost");
    conn->port = 5432;
    return conn;
}

// Function to execute a query and get the result
DatabaseResult* db_query(DatabaseConnection *conn, const char *query) {
    // Simulate database query execution
    DatabaseResult *result = (DatabaseResult*)malloc(sizeof(DatabaseResult));
    result->temperature = 21.5; // Mock temperature value
    return result;
}

// Function to free the database connection
void db_disconnect(DatabaseConnection *conn) {
    free(conn->host);
    free(conn);
}

// Function to parse payload and extract latitude, longitude, date
void parse_payload(const char *payload, float *latitude, float *longitude, char *date) {
    sscanf(payload, "lat=%f&lon=%f&date=%s", latitude, longitude, date);
}

// Function to handle temperature request for a location
float temperature_for_location(const char *payload) {
    float latitude, longitude;
    char date[1024];
    parse_payload(payload, &latitude, &longitude, date);

    // Connect to the database
    DatabaseConnection *conn = db_connect();

    // Construct the query
    char query[1024];
    snprintf(query, sizeof(query), "SELECT temperature FROM Sensor WHERE latitude=%f AND longitude=%f AND date='%s'", latitude, longitude, date);

    // Execute the query and get the result
    DatabaseResult *result = db_query(conn, query);
    float temperature = result->temperature;

    // Clean up resources
    free(result);
    db_disconnect(conn);

    return temperature;
}

int main() {
    const char *payload = "lat=37.7749&lon=-122.4194&date=2023-10-01";
    float temperature = temperature_for_location(payload);
    printf("Temperature: %.2f\n", temperature);
    return 0;
}