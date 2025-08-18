#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define SERVER "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "Sensor"

void temperature_for_location(const char *date) {
    MYSQL conn;
    MYSQL_ROW row;
    MYSQL_RES *res;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(&conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM sensor_data WHERE date = '%s'", date);

    if (mysql_query(&conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        exit(1);
    }

    res = mysql_store_result(&conn);

    if ((row = mysql_fetch_row(res))) {
        printf("Temperature: %s\n", row[0]);
    } else {
        printf("No temperature data found for the given date.\n");
    }

    mysql_free_result(res);
    mysql_close(&conn);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <date>\n", argv[0]);
        exit(1);
    }
    
    temperature_for_location(argv[1]);

    return 0;
}