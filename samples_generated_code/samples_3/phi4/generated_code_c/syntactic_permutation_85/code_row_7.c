#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "Sensor"

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD
} Payload;

void temperature_for_location(const Payload *payload) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[256];

    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    snprintf(query, sizeof(query), 
             "SELECT temperature FROM temperatures WHERE latitude = %lf AND longitude = %lf AND date = '%s'", 
             payload->latitude, payload->longitude, payload->date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    if ((row = mysql_fetch_row(res)) != NULL) {
        printf("Temperature: %s\n", row[0]);
    } else {
        printf("No temperature data found for the given location and date.\n");
    }

    mysql_free_result(res);
    mysql_close(conn);
}

int main() {
    Payload payload = {37.7749, -122.4194, "2023-10-01"};
    temperature_for_location(&payload);

    return 0;
}
