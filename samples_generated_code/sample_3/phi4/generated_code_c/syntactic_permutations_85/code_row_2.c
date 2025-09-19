#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
} LocationPayload;

double temperature_for_location(LocationPayload payload) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    const char *server = "localhost";
    const char *user = "your_username";
    const char *password = "your_password";
    const char *database = "Sensor";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM TemperatureRecords WHERE latitude = %f AND longitude = %f AND date = '%s'", 
             payload.latitude, payload.longitude, payload.date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_store_result(conn);

    if ((row = mysql_fetch_row(res))) {
        double temperature = atof(row[0]);
        mysql_free_result(res);
        mysql_close(conn);
        return temperature;
    } else {
        mysql_free_result(res);
        mysql_close(conn);
        fprintf(stderr, "No temperature data found for the given location and date.\n");
        exit(1);
    }
}

int main() {
    LocationPayload payload = {37.7749, -122.4194, "2023-10-01"};
    double temp = temperature_for_location(payload);
    printf("Temperature: %.2f\n", temp);
    return 0;
}