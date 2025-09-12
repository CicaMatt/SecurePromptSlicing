#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mysql/mysql.h>

void temperature_for_location(char *latitude, char *longitude, char *date) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "username"; // Replace with your username
    const char *password = "password"; // Replace with your password
    const char *database = "Sensor";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    sprintf(query, 
            "SELECT temperature FROM readings WHERE latitude = '%s' AND longitude = '%s' AND date = '%s'", 
            latitude, longitude, date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res))) {
        printf("Temperature: %s\n", row[0]);
    } else {
        printf("No temperature data found for the specified location and date.\n");
    }

    mysql_free_result(res);
    mysql_close(conn);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <latitude> <longitude> <date>\n", argv[0]);
        return EXIT_FAILURE;
    }

    temperature_for_location(argv[1], argv[2], argv[3]);

    return EXIT_SUCCESS;
}