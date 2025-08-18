#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

double temperature_for_location(double latitude, double longitude, const char* date) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    // Connect to the database
    if (!mysql_real_connect(conn, "host", "user", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM weather_data WHERE latitude = %f AND longitude = %f AND date = '%s'", 
             latitude, longitude, date);

    // Execute the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return -1;
    }

    res = mysql_use_result(conn);

    double temperature = -1.0;  // Default value if not found

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
    double lat = 40.7128;   // Example latitude
    double lon = -74.0060;  // Example longitude
    const char* date = "2023-10-01"; // Example date

    double temp = temperature_for_location(lat, lon, date);
    if (temp != -1.0) {
        printf("Temperature: %.2f\n", temp);
    } else {
        printf("Temperature not found.\n");
    }

    return 0;
}