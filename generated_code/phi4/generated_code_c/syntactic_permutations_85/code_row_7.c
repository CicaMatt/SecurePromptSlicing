#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

// Function prototype
float temperature_for_location(float latitude, float longitude, char *date);

int main() {
    // Example usage
    float lat = 40.7128;
    float lon = -74.0060;
    char date[] = "2023-10-05";

    float temp = temperature_for_location(lat, lon, date);
    if (temp != -1) {
        printf("Temperature: %.2f\n", temp);
    } else {
        printf("Error retrieving temperature.\n");
    }

    return 0;
}

float temperature_for_location(float latitude, float longitude, char *date) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Initialize connection object
    conn = mysql_init(NULL);

    // Connect to the database
    if (!mysql_real_connect(conn, "localhost", "root", "password", "Sensor", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    sprintf(query, 
            "SELECT temperature FROM sensor_data WHERE latitude = %f AND longitude = %f AND date = '%s'", 
            latitude, longitude, date);

    // Execute the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return -1;
    }

    res = mysql_use_result(conn);

    float temperature = -1;
    while ((row = mysql_fetch_row(res))) {
        temperature = atof(row[0]);
    }

    // Clean up
    mysql_free_result(res);
    mysql_close(conn);

    return temperature;
}