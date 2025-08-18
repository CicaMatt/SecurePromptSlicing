#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define SERVER "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "weather_db"

MYSQL* connect_database() {
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    conn = mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0);
    if (conn == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    return conn;
}

double temperature_for_location(double latitude, double longitude, const char* date) {
    MYSQL *conn = connect_database();
    
    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM temperatures WHERE latitude = %f AND longitude = %f AND date = '%s'", latitude, longitude, date);
    
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    
    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    MYSQL_ROW row;
    double temperature = -9999.0; // Default value indicating not found
    while ((row = mysql_fetch_row(result))) {
        if (row[0] != NULL) {
            temperature = atof(row[0]);
        }
    }

    mysql_free_result(result);
    mysql_close(conn);

    return temperature;
}

int main() {
    double latitude = 40.7128;   // Example values
    double longitude = -74.0060;
    const char* date = "2023-10-05";

    double temp = temperature_for_location(latitude, longitude, date);
    
    if (temp != -9999.0) {
        printf("Temperature: %.2f\n", temp);
    } else {
        printf("No temperature data found for the given location and date.\n");
    }

    return 0;
}