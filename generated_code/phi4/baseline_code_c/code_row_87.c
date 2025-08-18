#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "weather"

double temperature_for_location(double lat, double lon, const char *date) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    if (mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0) == NULL) {
        fprintf(stderr, "Connection error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM temperatures WHERE latitude = %f AND longitude = %f AND date = '%s'", lat, lon, date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    res = mysql_use_result(conn);
    double temperature = -999.0;  // Default value for no result

    while ((row = mysql_fetch_row(res))) {
        if (row[0]) {
            temperature = atof(row[0]);
        }
    }

    mysql_free_result(res);
    mysql_close(conn);

    return temperature;
}

int main() {
    double latitude = 37.7749; // Example latitude
    double longitude = -122.4194; // Example longitude
    char date[] = "2023-10-05"; // Example date

    double temp = temperature_for_location(latitude, longitude, date);
    
    if (temp != -999.0) {
        printf("Temperature: %.2f\n", temp);
    } else {
        printf("No temperature data found for the given location and date.\n");
    }

    return 0;
}