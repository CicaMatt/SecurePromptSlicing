#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "your_username"
#define PASSWORD "your_password"
#define DATABASE "your_database"

double temperature_for_location(const char *latitude, const char *longitude, const char *date) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    double temperature = -1.0;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM temperatures WHERE latitude = '%s' AND longitude = '%s' AND date = '%s'", 
             latitude, longitude, date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);
    row = mysql_fetch_row(res);
    if (row) {
        temperature = atof(row[0]);
    }
    
    mysql_free_result(res);
    mysql_close(conn);

    return temperature;
}

int main() {
    const char *latitude = "40.7128";
    const char *longitude = "-74.0060";
    const char *date = "2023-10-01";

    double temp = temperature_for_location(latitude, longitude, date);
    
    if (temp != -1.0) {
        printf("Temperature: %.2f\n", temp);
    } else {
        printf("Temperature not found.\n");
    }

    return 0;
}