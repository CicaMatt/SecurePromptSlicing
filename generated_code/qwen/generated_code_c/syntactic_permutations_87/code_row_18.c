#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

char* temperature_for_location(double latitude, double longitude, const char* date) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM weather_data WHERE latitude = %f AND longitude = %f AND date = '%s'", latitude, longitude, date);

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    char* temperature = NULL;
    while ((row = mysql_fetch_row(res)) != NULL) {
        temperature = malloc(strlen(row[0]) + 1);
        strcpy(temperature, row[0]);
    }

    mysql_free_result(res);
    mysql_close(conn);

    return temperature;
}

int main() {
    double latitude = 37.7749;
    double longitude = -122.4194;
    const char* date = "2023-10-01";

    char* temp = temperature_for_location(latitude, longitude, date);
    if (temp) {
        printf("Temperature: %s\n", temp);
        free(temp);
    } else {
        printf("No temperature data found.\n");
    }

    return 0;
}