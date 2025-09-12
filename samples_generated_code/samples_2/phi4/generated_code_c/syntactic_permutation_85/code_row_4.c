#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

typedef struct {
    char latitude[50];
    char longitude[50];
    char date[11]; // Format: YYYY-MM-DD
} LocationData;

double temperature_for_location(LocationData data) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    double temperature = -1.0;
    
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "MySQL initialization failed\n");
        exit(EXIT_FAILURE);
    }

    if (mysql_real_connect(conn, "localhost", "username", "password", "Sensor", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM readings WHERE latitude='%s' AND longitude='%s' AND date='%s'",
             data.latitude, data.longitude, data.date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    res = mysql_use_result(conn);
    row = mysql_fetch_row(res);
    if (row) {
        temperature = atof(row[0]);
    } else {
        printf("No data found for the given location and date.\n");
    }
    
    mysql_free_result(res);
    mysql_close(conn);

    return temperature;
}

int main() {
    LocationData data = {
        .latitude = "40.7128",
        .longitude = "-74.0060",
        .date = "2023-10-01"
    };

    double temp = temperature_for_location(data);
    if (temp != -1.0) {
        printf("Temperature: %.2f\n", temp);
    } else {
        printf("Failed to retrieve temperature.\n");
    }

    return 0;
}