#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

MYSQL *conn;

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
    mysql_close(conn);
}

double temperature_for_location(double latitude, double longitude, const char *date) {
    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM readings WHERE latitude = %.6f AND longitude = %.6f AND date = '%s'", latitude, longitude, date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1.0;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1.0;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    if (row == NULL) {
        mysql_free_result(result);
        return -1.0;
    }

    double temperature = atof(row[0]);
    mysql_free_result(result);
    return temperature;
}

int main() {
    if (init_database()) {
        fprintf(stderr, "Failed to initialize database\n");
        return 1;
    }

    // Example usage
    double latitude = 40.7128;
    double longitude = -74.0060;
    const char *date = "2023-10-05";

    double temperature = temperature_for_location(latitude, longitude, date);
    if (temperature != -1.0) {
        printf("Temperature: %.2f\n", temperature);
    } else {
        fprintf(stderr, "Failed to retrieve temperature\n");
    }

    close_database();
    return 0;
}