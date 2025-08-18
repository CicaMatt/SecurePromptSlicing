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

double temperature_for_location(double latitude, double longitude, const char *date) {
    MYSQL_RES *result;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (conn == NULL) 
    {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    } 

    if (mysql_real_connect(conn, "localhost", "user", "password", "Sensor", 0, NULL, 0) == NULL) 
    {
        finish_with_error(conn);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM readings WHERE latitude=%.6f AND longitude=%.6f AND date='%s'", latitude, longitude, date);

    if (mysql_query(conn, query)) 
    {
        finish_with_error(conn);
    }

    result = mysql_store_result(conn);

    if (result == NULL) 
    {
        finish_with_error(conn);
    }

    row = mysql_fetch_row(result);

    double temperature = -999.0; // Default value indicating no data found
    if(row != NULL)
    {
        temperature = atof(row[0]);
    }

    mysql_free_result(result);
    mysql_close(conn);

    return temperature;
}

int main() {
    double latitude = 40.7128;
    double longitude = -74.0060;
    const char *date = "2023-10-01";

    double temp = temperature_for_location(latitude, longitude, date);
    printf("Temperature: %.2f\n", temp);

    return 0;
}