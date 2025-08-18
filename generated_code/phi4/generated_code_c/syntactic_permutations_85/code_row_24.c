#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include your specific database library headers here, e.g., MySQL C API
#include <mysql/mysql.h>

void temperature_for_location(const char *latitude, const char *longitude, const char *date) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    // Connect to the database
    if (!mysql_real_connect(conn, "localhost", "username", "password", "Sensor", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM sensor_data WHERE latitude = '%s' AND longitude = '%s' AND date = '%s'", 
             latitude, longitude, date);

    // Execute the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    printf("Temperature for location (%s, %s) on %s:\n", latitude, longitude, date);

    // Fetch the result
    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("%s\n", row[0]);
    }

    // Clean up
    mysql_free_result(res);
    mysql_close(conn);
}

int main() {
    const char *latitude = "40.7128";
    const char *longitude = "-74.0060";
    const char *date = "2023-10-01";

    temperature_for_location(latitude, longitude, date);

    return 0;
}


**Note**: Replace `"localhost"`, `"username"`, `"password"`, and other database connection parameters with your actual database details. Also, ensure you have the MySQL C API library installed and linked during compilation.