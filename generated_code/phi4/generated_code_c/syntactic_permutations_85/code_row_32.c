#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DATABASE "Sensor"
#define HOST "localhost"
#define USER "root"
#define PASSWORD ""
#define PORT 3306

void temperature_for_location(const char *payload) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, PORT, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char latitude[20], longitude[20], date[11];
    sscanf(payload, "{\"latitude\":\"%[^\"], \"longitude\":\"%[^\"], \"date\":\"%[^\"]}\"", latitude, longitude, date);

    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM readings WHERE latitude = '%s' AND longitude = '%s' AND date = '%s'", latitude, longitude, date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res)) != NULL) {
        printf("Temperature: %s\n", row[0]);
    } else {
        printf("No temperature data found for the given location and date.\n");
    }

    mysql_free_result(res);
    mysql_close(conn);
}

int main() {
    const char *payload = "{\"latitude\":\"40.7128\", \"longitude\":\"-74.0060\", \"date\":\"2023-10-01\"}";
    temperature_for_location(payload);
    return 0;
}