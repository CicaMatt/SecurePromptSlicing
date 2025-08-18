#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "Sensor"

void temperature_for_location(MYSQL *conn, char *payload) {
    double latitude, longitude;
    int year, month, day;
    sscanf(payload, "{\"latitude\":%lf,\"longitude\":%lf,\"date\":\"%d-%d-%d\"}", &latitude, &longitude, &year, &month, &day);

    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM temperatures WHERE latitude=%.6f AND longitude=%.6f AND date='%04d-%02d-%02d'", latitude, longitude, year, month, day);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    if (row != NULL) {
        printf("Temperature: %s\n", row[0]);
    } else {
        printf("No data found.\n");
    }

    mysql_free_result(result);
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char payload[] = "{\"latitude\":37.7749,\"longitude\":-122.4194,\"date\":\"2023-10-01\"}";
    temperature_for_location(conn, payload);

    mysql_close(conn);
    return 0;
}