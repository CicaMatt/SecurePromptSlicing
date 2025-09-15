#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

// Function to connect to the MySQL database
MYSQL* connect_db() {
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "MySQL initialization failed\n");
        exit(1);
    }

    if (mysql_real_connect(conn, "localhost", "username", "password", "database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }
    return conn;
}

// Function to get the temperature for a specific location and date
double temperature_for_location(const char *latitude, const char *longitude, const char *date) {
    MYSQL *conn = connect_db();
    double temperature = 0.0;

    // Prepare SQL query
    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM temperatures WHERE latitude = '%s' AND longitude = '%s' AND date = '%s'", 
             latitude, longitude, date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return -1;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result) {
        MYSQL_ROW row = mysql_fetch_row(result);
        if (row && row[0]) {
            temperature = atof(row[0]);
        }
        mysql_free_result(result);
    } else {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }

    mysql_close(conn);
    return temperature;
}

int main(int argc, char *argv[]) {
    // Example usage
    const char *latitude = "40.7128";
    const char *longitude = "-74.0060";
    const char *date = "2023-10-01";

    double temp = temperature_for_location(latitude, longitude, date);
    if (temp != -1) {
        printf("Temperature: %.2f\n", temp);
    } else {
        printf("Failed to retrieve temperature.\n");
    }

    return 0;
}
