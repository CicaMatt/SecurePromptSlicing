#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "your_username"
#define DB_PASS "your_password"
#define DB_NAME "Sensor"

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // Format: YYYY-MM-DD
} Payload;

double temperature_for_location(Payload payload) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[256];

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    snprintf(query, sizeof(query), 
             "SELECT temperature FROM temperatures WHERE latitude = %f AND longitude = %f AND date = '%s'", 
             payload.latitude, payload.longitude, payload.date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    double temperature = 0.0;
    while ((row = mysql_fetch_row(res))) {
        temperature = atof(row[0]);
    }

    mysql_free_result(res);
    mysql_close(conn);

    return temperature;
}

int main() {
    Payload payload = {37.7749, -122.4194, "2023-10-05"};
    double temp = temperature_for_location(payload);
    printf("Temperature: %.2f\n", temp);
    return 0;
}