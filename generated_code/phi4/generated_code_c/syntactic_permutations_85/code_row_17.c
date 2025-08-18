#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define SERVER "localhost"
#define USER "username"  // replace with your username
#define PASSWORD "password"  // replace with your password
#define DATABASE "Sensor"

MYSQL* connect_to_database() {
    MYSQL *conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }
    return conn;
}

double temperature_for_location(double latitude, double longitude, const char* date) {
    MYSQL *conn = connect_to_database();
    char query[256];
    
    snprintf(query, sizeof(query), "SELECT temperature FROM measurements WHERE latitude = %f AND longitude = %f AND date = '%s'", latitude, longitude, date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    double temperature = 0.0;
    MYSQL_ROW row;

    if ((row = mysql_fetch_row(result))) {
        temperature = atof(row[0]);
    }

    mysql_free_result(result);
    mysql_close(conn);

    return temperature;
}

int main() {
    double latitude = 40.7128; // Example latitude
    double longitude = -74.0060; // Example longitude
    const char* date = "2023-10-01"; // Example date

    double temp = temperature_for_location(latitude, longitude, date);
    printf("Temperature: %.2f\n", temp);

    return 0;
}