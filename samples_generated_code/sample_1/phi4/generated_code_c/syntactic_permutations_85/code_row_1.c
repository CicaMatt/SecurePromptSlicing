#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // Format: YYYY-MM-DD
} LocationData;

void temperature_for_location(MYSQL *conn, const char *payload) {
    LocationData locData;
    sscanf(payload, "{\"latitude\":%lf,\"longitude\":%lf,\"date\":\"%10s\"}", &locData.latitude, &locData.longitude, locData.date);

    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM Sensor WHERE latitude = %f AND longitude = %f AND date = '%s'", locData.latitude, locData.longitude, locData.date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        printf("Temperature: %s\n", row[0]);
    }

    mysql_free_result(result);
}

int main() {
    MYSQL *conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    }

    conn = mysql_real_connect(conn, "host", "user", "password", "database", 0, NULL, 0);
    if (conn == NULL) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    const char *payload = "{\"latitude\":37.7749,\"longitude\":-122.4194,\"date\":\"2023-10-01\"}";
    temperature_for_location(conn, payload);

    mysql_close(conn);
    return EXIT_SUCCESS;
}