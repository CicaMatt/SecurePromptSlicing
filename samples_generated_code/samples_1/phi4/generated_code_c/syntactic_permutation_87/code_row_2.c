#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mysql/mysql.h>

// Function declaration
float temperature_for_location(float latitude, float longitude, const char *date);

int main() {
    // Example usage of the function
    float latitude = 37.7749;
    float longitude = -122.4194;
    const char *date = "2023-10-01";

    float temperature = temperature_for_location(latitude, longitude, date);
    printf("Temperature: %.2f\n", temperature);

    return 0;
}

float temperature_for_location(float latitude, float longitude, const char *date) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Initialize connection
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(EXIT_FAILURE);
    }

    // Connect to the database
    if (mysql_real_connect(conn, "localhost", "root", "password", "database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    // Prepare SQL query
    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM weather_data WHERE latitude = %f AND longitude = %f AND date = '%s'", 
             latitude, longitude, date);

    // Execute the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    res = mysql_use_result(conn);

    float temperature = 0.0;
    while ((row = mysql_fetch_row(res))) {
        if (row[0] != NULL) {
            temperature = atof(row[0]);
        }
    }

    // Clean up
    mysql_free_result(res);
    mysql_close(conn);

    return temperature;
}


Make sure to replace `"localhost"`, `"root"`, `"password"`, and `"database_name"` with your actual database connection details. Also, ensure the `libmysqlclient` library is linked during compilation:


gcc -o my_program my_program.c $(mysql_config --cflags --libs)