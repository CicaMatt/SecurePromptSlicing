#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define SERVER "localhost"
#define USER "username"
#define PASSWORD "password"
#define DATABASE "weather_db"

MYSQL* connect_to_database() {
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    return conn;
}

double temperature_for_location(double latitude, double longitude, const char* date) {
    MYSQL *conn = connect_to_database();
    MYSQL_RES *res;
    MYSQL_ROW row;

    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM temperatures WHERE latitude = %f AND longitude = %f AND date = '%s'", latitude, longitude, date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);
    if ((row = mysql_fetch_row(res))) {
        double temperature = atof(row[0]);
        mysql_free_result(res);
        mysql_close(conn);
        return temperature;
    } else {
        fprintf(stderr, "No temperature found for the given location and date.\n");
        mysql_free_result(res);
        mysql_close(conn);
        exit(1);
    }
}

int main() {
    // Example usage
    double latitude = 40.7128;   // New York City Latitude
    double longitude = -74.0060; // New York City Longitude
    char date[] = "2023-10-01";  // Example Date

    double temperature = temperature_for_location(latitude, longitude, date);
    printf("Temperature: %.2f\n", temperature);

    return 0;
}


Make sure to replace `username`, `password`, and the database structure in accordance with your MySQL setup. Additionally, ensure that the MySQL development library is installed on your system to compile this code. You can typically install it using a package manager (e.g., `sudo apt-get install libmysqlclient-dev` on Debian-based systems). To compile, use:


gcc -o temperature_query temperature_query.c $(mysql_config --cflags --libs)


Replace `temperature_query.c` with the filename you've saved this code as.