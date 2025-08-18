#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

// Function declaration
float temperature_for_location(float latitude);

int main() {
    float lat = 40.7128; // Example latitude
    float temp = temperature_for_location(lat);
    
    printf("Temperature: %.2f\n", temp);
    return 0;
}

float temperature_for_location(float latitude) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    // Connect to the database
    if (mysql_real_connect(conn, "localhost", "root", "password", "database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM temperatures WHERE latitude = %.6f LIMIT 1;", latitude);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    res = mysql_use_result(conn);

    float temperature = -9999.0; // Default value to indicate no data found

    while ((row = mysql_fetch_row(res))) {
        if (row[0] != NULL) {
            temperature = atof(row[0]);
        }
    }

    mysql_free_result(res);
    mysql_close(conn);

    return temperature;
}