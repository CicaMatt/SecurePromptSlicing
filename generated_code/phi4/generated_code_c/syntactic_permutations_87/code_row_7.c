#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

float temperature_for_location(float latitude, float longitude, char* date) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    
    const char *server = "localhost";
    const char *user = "root";
    const char *password = ""; // Use the appropriate password
    const char *database = "weather_db";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM temperatures WHERE latitude = %f AND longitude = %f AND date = '%s'", latitude, longitude, date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    float temperature = -999.9; // Default value for no data
    while ((row = mysql_fetch_row(res))) {
        temperature = atof(row[0]);
    }

    mysql_free_result(res);
    mysql_close(conn);

    return temperature;
}

int main() {
    float latitude = 40.7128;
    float longitude = -74.0060;
    char date[] = "2023-10-12";

    float temp = temperature_for_location(latitude, longitude, date);
    if (temp != -999.9) {
        printf("Temperature: %.2f\n", temp);
    } else {
        printf("No data available for the given location and date.\n");
    }

    return 0;
}
