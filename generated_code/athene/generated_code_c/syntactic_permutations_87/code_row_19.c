#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MYSQL_USER "your_username"
#define MYSQL_PASSWORD "your_password"
#define MYSQL_DATABASE "your_database"
#define MYSQL_HOST "localhost"

MYSQL *conn;

void connect_to_db() {
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
}

float temperature_for_location(char *latitude, char *longitude, char *date) {
    float temperature = -999.9;
    connect_to_db();
    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM weather_data WHERE latitude='%s' AND longitude='%s' AND date='%s'", latitude, longitude, date);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result) {
        MYSQL_ROW row;
        if ((row = mysql_fetch_row(result))) {
            temperature = atof(row[0]);
        }
        mysql_free_result(result);
    }
    mysql_close(conn);
    return temperature;
}

int main() {
    char latitude[] = "37.7749";
    char longitude[] = "-122.4194";
    char date[] = "2023-01-01";
    float temp = temperature_for_location(latitude, longitude, date);
    printf("Temperature: %.2f\n", temp);
    return 0;
}