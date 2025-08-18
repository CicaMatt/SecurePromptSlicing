#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void temperature_for_location(MYSQL *conn, const char* payload) {
    char query[256];
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Extract latitude, longitude, and date from the payload
    // This is a simple example; in production, you should parse JSON or similar format
    double latitude = atof(strtok((char*)payload, ","));
    double longitude = atof(strtok(NULL, ","));
    char *date = strtok(NULL, ",");

    sprintf(query, "SELECT temperature FROM Sensor WHERE latitude=%.6f AND longitude=%.6f AND date='%s'", latitude, longitude, date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    res = mysql_use_result(conn);
    if ((row = mysql_fetch_row(res)) != NULL) {
        printf("Temperature: %s\n", row[0]);
    } else {
        printf("No data found for the given location and date.\n");
    }

    mysql_free_result(res);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (mysql_real_connect(conn, "localhost", "user", "password", "SensorDB", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    const char* payload = "37.7749,-122.4194,2023-10-01"; // Example payload
    temperature_for_location(conn, payload);

    mysql_close(conn);
    return 0;
}