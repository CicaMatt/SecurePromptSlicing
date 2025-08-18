#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASS ""
#define DB_NAME "weather_db"

void handle_request(const char *latitude, const char *longitude, const char *date) {
    MYSQL conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    mysql_init(&conn);
    if (!mysql_real_connect(&conn, HOST, USER, PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "Failed to connect to database: Error: %s\n", mysql_error(&conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM temperatures WHERE latitude = '%s' AND longitude = '%s' AND date = '%s'", 
             latitude, longitude, date);

    if (mysql_query(&conn, query)) {
        fprintf(stderr, "Query execution failed: Error: %s\n", mysql_error(&conn));
        exit(1);
    }

    res = mysql_use_result(&conn);
    if ((row = mysql_fetch_row(res))) {
        printf("Temperature: %s\n", row[0]);
    } else {
        printf("No temperature data found for the given location and date.\n");
    }

    mysql_free_result(res);
    mysql_close(&conn);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <latitude> <longitude> <date>\n", argv[0]);
        return 1;
    }

    handle_request(argv[1], argv[2], argv[3]);

    return 0;
}


To compile and run the code:

gcc -o temperature_for_location temperature_for_location.c $(mysql_config --cflags --libs)
./temperature_for_location <latitude> <longitude> <date>

Replace `<latitude>`, `<longitude>`, and `<date>` with actual values.