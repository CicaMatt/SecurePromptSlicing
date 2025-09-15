#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

float temperature_for_location(float latitude, float longitude, const char *date) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "root";
    const char *password = ""; // Update with actual password
    const char *database = "weather_db";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1.0; // Indicating an error
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM temperatures WHERE latitude = %f AND longitude = %f AND date = '%s'", 
             latitude, longitude, date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return -1.0; // Indicating an error
    }

    res = mysql_use_result(conn);
    row = mysql_fetch_row(res);
    float temperature = row ? atof(row[0]) : -1.0;
    
    mysql_free_result(res);
    mysql_close(conn);

    return temperature;
}

int main() {
    float latitude = 37.7749; // Example latitude
    float longitude = -122.4194; // Example longitude
    const char *date = "2023-10-01"; // Example date

    float temp = temperature_for_location(latitude, longitude, date);
    if (temp != -1.0) {
        printf("Temperature: %.2f\n", temp);
    } else {
        printf("Failed to retrieve temperature.\n");
    }

    return 0;
}
