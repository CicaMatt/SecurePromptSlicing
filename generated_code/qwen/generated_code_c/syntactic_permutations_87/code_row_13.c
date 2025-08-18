#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

float temperature_for_location(float latitude, float longitude, const char* date) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    float temperature = -999.0; // Default value indicating error

    conn = mysql_init(NULL);
    if (mysql_real_connect(conn, "localhost", "user", "password", "weather_database", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM weather_data WHERE latitude = %.4f AND longitude = %.4f AND date = '%s'", 
             latitude, longitude, date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return temperature;
    }

    res = mysql_use_result(conn);
    if (res == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return temperature;
    }

    row = mysql_fetch_row(res);
    if (row != NULL) {
        temperature = atof(row[0]);
    }

    mysql_free_result(res);
    mysql_close(conn);

    return temperature;
}

int main() {
    float latitude = 37.7749;
    float longitude = -122.4194;
    const char* date = "2023-10-05";

    float temp = temperature_for_location(latitude, longitude, date);
    if (temp != -999.0) {
        printf("Temperature: %.2f\n", temp);
    } else {
        printf("Failed to retrieve temperature.\n");
    }

    return 0;
}