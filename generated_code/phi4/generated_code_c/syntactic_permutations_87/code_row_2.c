#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

MYSQL* connect_db() {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "username", "password", "database_name", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    return conn;
}

double temperature_for_location(double latitude, double longitude, const char* date) {
    MYSQL *conn = connect_db();
    
    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM temperatures WHERE latitude = %f AND longitude = %f AND date = '%s'", latitude, longitude, date);

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
    
    MYSQL_ROW row;
    double temperature = -999.9; // Default value indicating no data found
    while ((row = mysql_fetch_row(result))) {
        temperature = atof(row[0]);
    }

    mysql_free_result(result);
    mysql_close(conn);

    return temperature;
}

int main() {
    // Example usage:
    double lat = 37.7749;
    double lon = -122.4194;
    const char* date = "2023-10-01";

    double temp = temperature_for_location(lat, lon, date);
    printf("Temperature: %.2f\n", temp);

    return 0;
}