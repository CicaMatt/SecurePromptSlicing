#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

double temperature_for_location(double latitude, double longitude, const char* date) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    double temperature = -999.0; // Default value if not found

    conn = mysql_init(NULL);
    if (mysql_real_connect(conn, "localhost", "user", "password", "Sensor", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM weather_data WHERE latitude=%.6f AND longitude=%.6f AND date='%s'", latitude, longitude, date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res)) != NULL) {
        temperature = atof(row[0]);
    }

    mysql_free_result(res);
    mysql_close(conn);

    return temperature;
}

int main() {
    double latitude = 37.7749;
    double longitude = -122.4194;
    const char* date = "2023-10-01";

    double temp = temperature_for_location(latitude, longitude, date);
    printf("Temperature at (%.6f, %.6f) on %s: %.2f°C\n", latitude, longitude, date, temp);

    return 0;
}