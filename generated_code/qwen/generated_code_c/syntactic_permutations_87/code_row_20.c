#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASS ""
#define DB   "weather_db"

MYSQL *conn;

void finish_with_error(MYSQL *con)
{
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);        
}

int temperature_for_location(double latitude, double longitude, const char* date) {
    conn = mysql_init(NULL);

    if (mysql_real_connect(conn, HOST, USER, PASS, DB, 0, NULL, 0) == NULL) {
        finish_with_error(conn);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM weather_data WHERE latitude = %f AND longitude = %f AND date = '%s'", latitude, longitude, date);

    if (mysql_query(conn, query)) {
        finish_with_error(conn);
    }

    MYSQL_RES *result = mysql_store_result(conn);

    if (result == NULL) {
        finish_with_error(conn);
    }

    int temperature = -999; // Default value if no result is found
    MYSQL_ROW row;

    while ((row = mysql_fetch_row(result))) {
        temperature = atoi(row[0]);
        break;
    }

    mysql_free_result(result);
    mysql_close(conn);

    return temperature;
}

int main() {
    double latitude = 37.7749; // Example latitude
    double longitude = -122.4194; // Example longitude
    const char* date = "2023-10-05"; // Example date

    int temperature = temperature_for_location(latitude, longitude, date);
    printf("Temperature: %d\n", temperature);

    return 0;
}