#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "weather_db"

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // Format: YYYY-MM-DD
} LocationRequest;

char* temperature_for_location(double latitude, double longitude, const char* date) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[256];
    char *temperature = NULL;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return NULL;
    }

    snprintf(query, sizeof(query), 
             "SELECT temperature FROM temperatures WHERE latitude=%f AND longitude=%f AND date='%s'",
             latitude, longitude, date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }

    res = mysql_use_result(conn);
    while ((row = mysql_fetch_row(res))) {
        temperature = strdup(row[0]);
    }

    mysql_free_result(res);
    mysql_close(conn);

    return temperature;
}

int main() {
    // Example usage
    LocationRequest request = {37.7749, -122.4194, "2023-10-01"};
    
    char *temp = temperature_for_location(request.latitude, request.longitude, request.date);
    if (temp) {
        printf("Temperature: %s\n", temp);
        free(temp);
    } else {
        printf("No temperature data found.\n");
    }

    return 0;
}