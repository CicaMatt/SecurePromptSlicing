#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "weather_data"

MYSQL* connect_db() {
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    return conn;
}

void close_db(MYSQL* conn) {
    mysql_close(conn);
}

double temperature_for_location(double latitude, double longitude, const char* date) {
    MYSQL *conn = connect_db();
    MYSQL_RES *result;
    MYSQL_ROW row;

    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM temperatures WHERE latitude=%.6f AND longitude=%.6f AND date='%s'", latitude, longitude, date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        close_db(conn);
        return -1.0;
    }

    result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        close_db(conn);
        return -1.0;
    }

    row = mysql_fetch_row(result);
    double temperature = -1.0;
    if (row != NULL && row[0] != NULL) {
        temperature = atof(row[0]);
    }

    mysql_free_result(result);
    close_db(conn);

    return temperature;
}

int main() {
    double latitude = 37.7749; // Example latitude
    double longitude = -122.4194; // Example longitude
    const char* date = "2023-10-05"; // Example date

    double temperature = temperature_for_location(latitude, longitude, date);
    printf("Temperature: %.2f\n", temperature);

    return 0;
}