#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void temperature_for_location(const char *latitude, const char *longitude, const char *date) {
    MYSQL conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    mysql_init(&conn);

    if (!mysql_real_connect(&conn, "localhost", "username", "password", "Sensor", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM readings WHERE latitude = '%s' AND longitude = '%s' AND date = '%s'", 
             latitude, longitude, date);

    if (mysql_query(&conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        exit(1);
    }

    res = mysql_store_result(&conn);

    if ((row = mysql_fetch_row(res))) {
        printf("Temperature: %s\n", row[0]);
    } else {
        printf("No temperature data found for the given location and date.\n");
    }

    mysql_free_result(res);
    mysql_close(&conn);
}

int main() {
    const char *latitude = "40.712776";
    const char *longitude = "-74.005974";
    const char *date = "2023-10-01";

    temperature_for_location(latitude, longitude, date);

    return 0;
}
