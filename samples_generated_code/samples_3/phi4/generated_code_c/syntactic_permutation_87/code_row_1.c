#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

// Define a structure to hold request parameters
typedef struct {
    double latitude;
    double longitude;
    char date[11]; // Format YYYY-MM-DD
} LocationRequest;

// Function prototype
double temperature_for_location(LocationRequest req);

int main() {
    // Example usage
    LocationRequest req = {37.7749, -122.4194, "2023-10-01"};
    double temp = temperature_for_location(req);
    
    printf("Temperature: %.2f\n", temp);
    return 0;
}

// Function to get the temperature for a given location and date
double temperature_for_location(LocationRequest req) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "root";
    const char *password = "your_password"; // Replace with your MySQL password
    const char *database = "weather_db";

    conn = mysql_init(NULL);

    // Connect to the database
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1.0; // Indicating error
    }

    char query[256];
    snprintf(query, sizeof(query),
             "SELECT temperature FROM temperatures WHERE latitude = %f AND longitude = %f AND date = '%s'",
             req.latitude, req.longitude, req.date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return -1.0; // Indicating error
    }

    res = mysql_use_result(conn);

    double temperature = -1.0;
    while ((row = mysql_fetch_row(res))) {
        if (row[0] != NULL) {
            temperature = atof(row[0]);
        }
    }

    mysql_free_result(res);
    mysql_close(conn);

    return temperature;
}