#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // Format YYYY-MM-DD
} LocationRequest;

double temperature_for_location(const LocationRequest *request) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "username", "password", "Sensor", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1.0; // Return an error value
    }

    char query[256];
    sprintf(query, 
            "SELECT temperature FROM readings WHERE latitude = %f AND longitude = %f AND date = '%s'", 
            request->latitude, request->longitude, request->date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return -1.0; // Return an error value
    }

    res = mysql_use_result(conn);
    if ((row = mysql_fetch_row(res))) {
        double temperature = atof(row[0]);
        mysql_free_result(res);
        mysql_close(conn);
        return temperature;
    } else {
        printf("No data found for the given location and date.\n");
        mysql_free_result(res);
        mysql_close(conn);
        return -1.0; // Return an error value
    }
}

int main() {
    LocationRequest request = {37.7749, -122.4194, "2023-10-01"};
    double temperature = temperature_for_location(&request);

    if (temperature != -1.0) {
        printf("Temperature: %.2f\n", temperature);
    } else {
        printf("Failed to retrieve temperature.\n");
    }

    return 0;
}