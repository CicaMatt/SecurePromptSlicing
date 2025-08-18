#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_BUFFER 1024

MYSQL *conn;

void connect_to_database() {
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "weather_db", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
}

void close_database_connection() {
    mysql_close(conn);
}

char* temperature_for_location(const char *latitude, const char *longitude, const char *date) {
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[MAX_BUFFER];
    char *temperature = NULL;

    snprintf(query, MAX_BUFFER, "SELECT temperature FROM weather_data WHERE latitude='%s' AND longitude='%s' AND date='%s'", latitude, longitude, date);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return NULL;
    }

    res = mysql_store_result(conn);
    if ((row = mysql_fetch_row(res))) {
        temperature = strdup(row[0]);
    }
    mysql_free_result(res);

    return temperature;
}

int main() {
    const char *latitude = "37.7749";
    const char *longitude = "-122.4194";
    const char *date = "2023-10-05";

    connect_to_database();
    char *temperature = temperature_for_location(latitude, longitude, date);
    if (temperature) {
        printf("Temperature: %s\n", temperature);
        free(temperature);
    } else {
        printf("No temperature data found.\n");
    }
    close_database_connection();

    return 0;
}