#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "Sensor"

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;

void handle_temperature_request(const char* payload) {
    double latitude, longitude;
    char date[11];
    
    // Parse the payload to extract latitude, longitude, and date
    sscanf(payload, "{\"latitude\":%lf,\"longitude\":%lf,\"date\":\"%10s\"}", &latitude, &longitude, date);

    // Initialize MySQL connection
    conn = mysql_init(NULL);
    if (mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "Failed to connect to database: %s\n", mysql_error(conn));
        exit(1);
    }

    // Prepare the SQL query
    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM temperatures WHERE latitude = %.6f AND longitude = %.6f AND date = '%s'", latitude, longitude, date);

    // Execute the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "Failed to execute query: %s\n", mysql_error(conn));
        exit(1);
    }

    // Get the result set
    res = mysql_use_result(conn);
    if (res == NULL) {
        fprintf(stderr, "No results returned.\n");
        exit(1);
    }

    // Fetch and print the temperature
    row = mysql_fetch_row(res);
    if (row != NULL && row[0] != NULL) {
        printf("Temperature: %s\n", row[0]);
    } else {
        printf("No temperature data found for the given location and date.\n");
    }

    // Clean up
    mysql_free_result(res);
    mysql_close(conn);
}

int main() {
    // Example payload
    const char* payload = "{\"latitude\":37.7749,\"longitude\":-122.4194,\"date\":\"2023-10-05\"}";
    
    handle_temperature_request(payload);

    return 0;
}