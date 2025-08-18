#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define SERVER "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "weather_db"

// Function to get temperature for a given location and date
double temperature_for_location(double latitude, double longitude, const char* date) {
    MYSQL conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Initialize connection handler
    mysql_init(&conn);

    // Connect to the database
    if (!mysql_real_connect(&conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM temperatures WHERE latitude = %f AND longitude = %f AND date = '%s'", 
             latitude, longitude, date);

    // Execute the query
    if (mysql_query(&conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        exit(1);
    }

    res = mysql_store_result(&conn);

    if ((row = mysql_fetch_row(res))) {
        double temperature = atof(row[0]);
        mysql_free_result(res);
        mysql_close(&conn);
        return temperature;
    } else {
        fprintf(stderr, "No data found for the given coordinates and date.\n");
        mysql_free_result(res);
        mysql_close(&conn);
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <latitude> <longitude> <date>\n", argv[0]);
        return 1;
    }

    double latitude = atof(argv[1]);
    double longitude = atof(argv[2]);
    const char *date = argv[3];

    double temperature = temperature_for_location(latitude, longitude, date);
    printf("Temperature: %.2f\n", temperature);

    return 0;
}