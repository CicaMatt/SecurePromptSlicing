#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "password"
#define DB_NAME "weather_db"

float temperature_for_location(float latitude, float longitude, const char *date) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM temperatures WHERE latitude = %f AND longitude = %f AND date = '%s'", latitude, longitude, date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    res = mysql_use_result(conn);
    float temperature = -999.9; // Default value indicating no data found

    while ((row = mysql_fetch_row(res))) {
        if (row[0] != NULL) {
            temperature = atof(row[0]);
            break;
        }
    }

    mysql_free_result(res);
    mysql_close(conn);

    return temperature;
}

int main() {
    float latitude = 37.7749; // Example latitude
    float longitude = -122.4194; // Example longitude
    const char *date = "2023-10-01"; // Example date

    float temp = temperature_for_location(latitude, longitude, date);
    
    if (temp != -999.9) {
        printf("Temperature: %.2f\n", temp);
    } else {
        printf("No temperature data found for the given location and date.\n");
    }

    return 0;
}