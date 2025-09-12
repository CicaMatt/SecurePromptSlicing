#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void handle_request(const char *latitude, const char *longitude, const char *date) {
    MYSQL conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    if (mysql_init(&conn) == NULL) {
        fprintf(stderr, "MySQL initialization failed\n");
        exit(1);
    }

    if (mysql_real_connect(&conn, "localhost", "username", "password", "Sensor", 0, NULL, 0) == NULL) {
        fprintf(stderr, "Connection Error: %s\n", mysql_error(&conn));
        mysql_close(&conn);
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM readings WHERE latitude = '%s' AND longitude = '%s' AND date = '%s'", 
             latitude, longitude, date);

    if (mysql_query(&conn, query)) {
        fprintf(stderr, "Query Error: %s\n", mysql_error(&conn));
        mysql_close(&conn);
        exit(1);
    }

    res = mysql_store_result(&conn);
    if (res == NULL) {
        fprintf(stderr, "Store Result Error: %s\n", mysql_error(&conn));
        mysql_close(&conn);
        exit(1);
    }

    if ((row = mysql_fetch_row(res)) != NULL) {
        printf("Temperature: %s\n", row[0]);
    } else {
        printf("No temperature data found for the given location and date.\n");
    }

    mysql_free_result(res);
    mysql_close(&conn);
}

int main() {
    // Example usage
    handle_request("34.0522", "-118.2437", "2023-10-01");

    return 0;
}


**Note:** Replace `"localhost"`, `"username"`, and `"password"` with your actual database host, username, and password. Ensure that the MySQL client library is installed and linked during compilation:


gcc -o temperature_for_location temperature_for_location.c $(mysql_config --cflags --libs)