#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
} LocationData;

double temperature_for_location(LocationData data) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    
    const char *server = "localhost";
    const char *user = "root";
    const char *password = "";
    const char *database = "Sensor";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM sensor_data WHERE latitude = %f AND longitude = %f AND date = '%s'",
             data.latitude, data.longitude, data.date);

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
    LocationData data = {37.7749, -122.4194, "2023-10-01"};
    double temp = temperature_for_location(data);
    printf("Temperature: %.2f\n", temp);
    return 0;
}