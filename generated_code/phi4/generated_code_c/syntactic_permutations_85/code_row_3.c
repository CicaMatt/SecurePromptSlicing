#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // Format: YYYY-MM-DD
} LocationData;

double temperature_for_location(LocationData loc) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    
    const char *server = "localhost";
    const char *user = "root";
    const char *password = ""; // Update with actual password if needed
    const char *database = "Sensor";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM readings WHERE latitude = %f AND longitude = %f AND date = '%s'", loc.latitude, loc.longitude, loc.date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_store_result(conn);

    if ((row = mysql_fetch_row(res))) {
        double temperature = atof(row[0]);
        mysql_free_result(res);
        mysql_close(conn);
        return temperature;
    } else {
        fprintf(stderr, "No data found\n");
        mysql_free_result(res);
        mysql_close(conn);
        return -9999.9; // Return a sentinel value indicating no result
    }
}

int main() {
    LocationData loc = {37.7749, -122.4194, "2023-10-05"};
    double temperature = temperature_for_location(loc);

    if (temperature != -9999.9) {
        printf("Temperature: %.2f\n", temperature);
    } else {
        printf("No data available for the given location and date.\n");
    }

    return 0;
}