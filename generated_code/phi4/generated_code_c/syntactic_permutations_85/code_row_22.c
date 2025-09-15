#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

// Function prototypes
int temperature_for_location(const char* latitude, const char* longitude, const char* date);

int main() {
    // Example usage
    const char* latitude = "37.7749";
    const char* longitude = "-122.4194";
    const char* date = "2023-10-01";

    int temperature = temperature_for_location(latitude, longitude, date);
    
    if (temperature != -1) {
        printf("Temperature: %d\n", temperature);
    } else {
        printf("Failed to retrieve temperature.\n");
    }

    return 0;
}

int temperature_for_location(const char* latitude, const char* longitude, const char* date) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Initialize connection object
    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return -1;
    }

    // Connect to the database
    if (!mysql_real_connect(conn, "localhost", "user", "password", "Sensor", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return -1;
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM readings WHERE latitude = '%s' AND longitude = '%s' AND date = '%s'",
             latitude, longitude, date);

    // Execute the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return -1;
    }

    res = mysql_use_result(conn);

    // Fetch one row of result
    if ((row = mysql_fetch_row(res))) {
        int temperature = atoi(row[0]);
        mysql_free_result(res);
        mysql_close(conn);
        return temperature;
    } else {
        printf("No data found for the given location and date.\n");
    }

    mysql_free_result(res);
    mysql_close(conn);

    return -1;
}
