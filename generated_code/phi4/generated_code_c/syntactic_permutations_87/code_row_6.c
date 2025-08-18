#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "password"
#define DB_NAME "weather_db"

void handle_request(const char *latitude, const char *longitude, const char *date) {
    MYSQL conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Initialize MySQL connection
    mysql_init(&conn);

    if (!mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "MySQL connection error: %s\n", mysql_error(&conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM weather_data WHERE latitude = '%s' AND longitude = '%s' AND date = '%s'", 
             latitude, longitude, date);

    if (mysql_query(&conn, query)) {
        fprintf(stderr, "MySQL query error: %s\n", mysql_error(&conn));
        mysql_close(&conn);
        exit(1);
    }

    res = mysql_store_result(&conn);
    if (!res) {
        fprintf(stderr, "MySQL result error: %s\n", mysql_error(&conn));
        mysql_close(&conn);
        exit(1);
    }

    if ((row = mysql_fetch_row(res))) {
        printf("Temperature: %s\n", row[0]);
    } else {
        printf("No temperature data found for the given coordinates and date.\n");
    }

    mysql_free_result(res);
    mysql_close(&conn);
}

int main() {
    // Example usage
    const char *latitude = "40.7128";
    const char *longitude = "-74.0060";
    const char *date = "2023-10-01";

    handle_request(latitude, longitude, date);

    return 0;
}


To compile and run this code, ensure you have the MySQL client library installed on your system. You can compile it using:


gcc -o weather_app weather_app.c $(mysql_config --cflags --libs)
./weather_app


Make sure to replace `DB_USER`, `DB_PASS`, and `DB_NAME` with your actual database credentials.