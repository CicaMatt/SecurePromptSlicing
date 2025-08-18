#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MYSQL_USER "user"
#define MYSQL_PASSWORD "password"
#define MYSQL_DATABASE "weather_db"

double get_temperature(MYSQL *conn, const char *latitude, const char *longitude, const char *date) {
    double temperature = -999.0;
    char query[256];
    MYSQL_RES *res;
    MYSQL_ROW row;

    snprintf(query, sizeof(query), "SELECT temperature FROM weather_data WHERE latitude='%s' AND longitude='%s' AND date='%s'", latitude, longitude, date);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return temperature;
    }

    res = mysql_store_result(conn);
    if (res) {
        row = mysql_fetch_row(res);
        if (row && row[0]) {
            sscanf(row[0], "%lf", &temperature);
        }
        mysql_free_result(res);
    }

    return temperature;
}

double temperature_for_location(const char *latitude, const char *longitude, const char *date) {
    MYSQL *conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return -999.0;
    }

    double temperature = get_temperature(conn, latitude, longitude, date);

    mysql_close(conn);
    return temperature;
}

int main() {
    const char *latitude = "37.7749";
    const char *longitude = "-122.4194";
    const char *date = "2023-10-01";

    double temperature = temperature_for_location(latitude, longitude, date);
    printf("Temperature: %.2f\n", temperature);

    return 0;
}