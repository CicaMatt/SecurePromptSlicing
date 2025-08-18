#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;

int init_database() {
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return 1;
    }
    if (mysql_real_connect(conn, "localhost", "user", "password", "Sensor", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }
    return 0;
}

void close_database() {
    mysql_free_result(res);
    mysql_close(conn);
}

int temperature_for_location(double latitude, double longitude, const char *date) {
    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM sensor_data WHERE latitude = %f AND longitude = %f AND date = '%s'", latitude, longitude, date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "mysql_store_result() failed\n");
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    row = mysql_fetch_row(res);
    if (row == NULL) {
        printf("No temperature data found.\n");
        return -1;
    }

    int temperature = atoi(row[0]);
    printf("Temperature: %d\n", temperature);
    return temperature;
}

int main() {
    if (init_database()) {
        return 1;
    }

    double latitude = 37.7749; // Example latitude
    double longitude = -122.4194; // Example longitude
    const char *date = "2023-10-01"; // Example date

    temperature_for_location(latitude, longitude, date);

    close_database();
    return 0;
}