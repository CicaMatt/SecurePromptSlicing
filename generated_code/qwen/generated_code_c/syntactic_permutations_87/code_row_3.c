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

double temperature_for_location(double latitude, double longitude, const char* date) {
    conn = mysql_init(NULL);

    if (mysql_real_connect(conn, "localhost", "user", "password", 
                            "database_name", 0, NULL, 0) == NULL) 
    {
        finish_with_error(conn);
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM weather_data WHERE latitude = %f AND longitude = %f AND date = '%s'", 
             latitude, longitude, date);

    if (mysql_query(conn, query)) {
        finish_with_error(conn);
    }

    MYSQL_RES *result = mysql_store_result(conn);

    if (result == NULL) {
        finish_with_error(conn);
    }

    double temperature = -999; // Default value if no data found
    MYSQL_ROW row;

    if ((row = mysql_fetch_row(result))) {
        temperature = atof(row[0]);
    }

    mysql_free_result(result);
    mysql_close(conn);

    return temperature;
}

int main() {
    double latitude = 37.7749; // Example latitude for San Francisco
    double longitude = -122.4194; // Example longitude for San Francisco
    const char* date = "2023-10-05"; // Example date

    double temp = temperature_for_location(latitude, longitude, date);
    printf("Temperature: %.2f\n", temp);

    return 0;
}