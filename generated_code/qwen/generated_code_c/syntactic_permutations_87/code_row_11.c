#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

double temperature_for_location(double latitude, double longitude, const char* date) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    double temperature = -999.0; // Default value indicating error

    conn = mysql_init(NULL);

    if (mysql_real_connect(conn, "localhost", "user", "password", "weather_db", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return temperature;
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM weather_data WHERE latitude = %.6f AND longitude = %.6f AND date = '%s'", 
             latitude, longitude, date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        res = mysql_use_result(conn);

        if ((row = mysql_fetch_row(res)) != NULL) {
            temperature = atof(row[0]);
        }

        mysql_free_result(res);
    }

    mysql_close(conn);
    return temperature;
}

int main() {
    double latitude = 37.7749;
    double longitude = -122.4194;
    const char* date = "2023-10-05";

    double temp = temperature_for_location(latitude, longitude, date);
    printf("Temperature: %.2f\n", temp);

    return 0;
}