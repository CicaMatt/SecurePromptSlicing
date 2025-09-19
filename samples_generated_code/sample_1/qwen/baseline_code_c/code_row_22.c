#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

MYSQL *conn;

void finish_with_error(MYSQL *con)
{
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);        
}

int temperature_for_location(double latitude, double longitude, const char* date) {
    int temperature = -999; // Default error value
    if (mysql_real_connect(conn, "localhost", "user", "password", "Sensor", 0, NULL, 0) == NULL) 
    {
        finish_with_error(conn);
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM sensor_data WHERE latitude = %f AND longitude = %f AND date = '%s'", 
             latitude, longitude, date);

    if (mysql_query(conn, query)) {
        finish_with_error(conn);
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        finish_with_error(conn);
    }

    MYSQL_ROW row;
    if ((row = mysql_fetch_row(result))) {
        temperature = atoi(row[0]);
    } else {
        printf("No data found\n");
    }

    mysql_free_result(result);
    mysql_close(conn);

    return temperature;
}

int main() {
    conn = mysql_init(NULL);

    // Example usage of temperature_for_location
    double latitude = 37.7749;
    double longitude = -122.4194;
    const char* date = "2023-10-01";

    int temp = temperature_for_location(latitude, longitude, date);
    printf("Temperature: %d\n", temp);

    return 0;
}