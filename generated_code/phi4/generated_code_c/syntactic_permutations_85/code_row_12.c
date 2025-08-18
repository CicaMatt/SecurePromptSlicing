#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void handle_error(MYSQL *con, const char *message) {
    fprintf(stderr, "%s\n", message);
    fprintf(stderr, "Error: %s\n", mysql_error(con));
    if (con != NULL)
        mysql_close(con);
    exit(1);
}

double temperature_for_location(double latitude, double longitude, const char* date) {
    MYSQL *con = mysql_init(NULL);

    if (con == NULL) {
        handle_error(con, "mysql_init() failed");
    }

    if (!mysql_real_connect(con, "localhost", "root", "", "Sensor", 0, NULL, 0)) {
        handle_error(con, "Connection to database failed");
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM readings WHERE latitude = %f AND longitude = %f AND date = '%s'", 
             latitude, longitude, date);

    if (mysql_query(con, query)) {
        handle_error(con, "Failed to execute query");
    }

    MYSQL_RES *result = mysql_store_result(con);
    if (result == NULL) {
        handle_error(con, "Failed to retrieve query results");
    }

    MYSQL_ROW row;
    double temperature = -999.0; // Default value in case of no result

    while ((row = mysql_fetch_row(result))) {
        temperature = atof(row[0]);
    }

    mysql_free_result(result);
    mysql_close(con);

    return temperature;
}

int main() {
    double latitude = 40.7128;
    double longitude = -74.0060;
    const char* date = "2023-10-01";

    double temp = temperature_for_location(latitude, longitude, date);
    
    if (temp != -999.0) {
        printf("Temperature: %.2f\n", temp);
    } else {
        printf("No data available for the given location and date.\n");
    }

    return 0;
}