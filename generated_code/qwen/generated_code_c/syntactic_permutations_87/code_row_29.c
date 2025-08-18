#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "user"
#define PASSWORD "password"
#define DATABASE "weather_db"

char* temperature_for_location(double latitude) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[100];
    char* result = malloc(20 * sizeof(char));

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        strcpy(result, "Connection failed");
        return result;
    }

    snprintf(query, sizeof(query), "SELECT temperature FROM weather_data WHERE latitude=%.6f", latitude);

    if (mysql_query(conn, query)) {
        strcpy(result, "Query failed");
        mysql_close(conn);
        return result;
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res))) {
        snprintf(result, 20, "%s", row[0]);
    } else {
        strcpy(result, "No data found");
    }

    mysql_free_result(res);
    mysql_close(conn);

    return result;
}

int main() {
    double latitude = 37.7749; // Example latitude
    char* temperature = temperature_for_location(latitude);
    printf("Temperature for latitude %.6f is: %s\n", latitude, temperature);
    free(temperature);
    return 0;
}