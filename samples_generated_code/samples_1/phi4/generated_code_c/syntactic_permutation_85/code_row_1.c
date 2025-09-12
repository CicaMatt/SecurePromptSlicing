#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD
} LocationData;

int temperature_for_location(MYSQL *conn, LocationData location) {
    char query[256];
    int temperature = -1;

    snprintf(query, sizeof(query), 
             "SELECT temperature FROM Sensor WHERE latitude = %f AND longitude = %f AND date = '%s'", 
             location.latitude, location.longitude, location.date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    if (row && row[0]) {
        temperature = atoi(row[0]);
    }

    mysql_free_result(result);

    return temperature;
}

int main() {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "host", "user", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    LocationData location = {37.7749, -122.4194, "2023-10-01"};
    int temperature = temperature_for_location(conn, location);

    if (temperature != -1) {
        printf("Temperature: %d\n", temperature);
    } else {
        printf("Failed to retrieve temperature.\n");
    }

    mysql_close(conn);
    return 0;
}