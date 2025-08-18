#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MYSQL_HOST "localhost"
#define MYSQL_USER "root"
#define MYSQL_PASSWORD ""
#define MYSQL_DATABASE "Sensor"

// Function to fetch temperature from database
double get_temperature(double latitude, double longitude, const char *date) {
    MYSQL conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    if (mysql_init(&conn) == NULL) {
        fprintf(stderr, "MySQL initialization failed\n");
        return -1.0;
    }

    if (mysql_real_connect(&conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD,
                           MYSQL_DATABASE, 0, NULL, 0) == NULL) {
        fprintf(stderr, "Connection error: %s\n", mysql_error(&conn));
        mysql_close(&conn);
        return -1.0;
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM temperatures WHERE latitude = %f AND longitude = %f AND date = '%s'",
             latitude, longitude, date);

    if (mysql_query(&conn, query)) {
        fprintf(stderr, "Query error: %s\n", mysql_error(&conn));
        mysql_close(&conn);
        return -1.0;
    }

    res = mysql_store_result(&conn);
    if (res == NULL) {
        fprintf(stderr, "MySQL store result failed: %s\n", mysql_error(&conn));
        mysql_close(&conn);
        return -1.0;
    }

    row = mysql_fetch_row(res);
    double temperature = row ? atof(row[0]) : -1.0;

    mysql_free_result(res);
    mysql_close(&conn);

    return temperature;
}

// Function to handle the API request
void api_temperature_for_location(char *payload, char *response) {
    // Example payload format: "latitude=40.7128&longitude=-74.0060&date=2023-10-01"
    
    double latitude = 0.0;
    double longitude = 0.0;
    char date[11] = {0};

    sscanf(payload, "latitude=%lf&longitude=%lf&date=%10s", &latitude, &longitude, date);

    double temperature = get_temperature(latitude, longitude, date);
    
    if (temperature == -1.0) {
        strcpy(response, "{\"error\": \"Unable to retrieve temperature\"}");
    } else {
        snprintf(response, 128, "{\"temperature\": %.2f}", temperature);
    }
}

int main() {
    char payload[] = "latitude=40.7128&longitude=-74.0060&date=2023-10-01";
    char response[128];

    api_temperature_for_location(payload, response);

    printf("%s\n", response);

    return 0;
}