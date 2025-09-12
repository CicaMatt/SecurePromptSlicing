#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASS ""
#define DB "weather_data"

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;

void handle_error() {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
}

double temperature_for_location(double latitude, double longitude, const char* date) {
    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM weather WHERE latitude = %f AND longitude = %f AND date = '%s'", 
             latitude, longitude, date);

    if (mysql_query(conn, query)) {
        handle_error();
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        handle_error();
    }

    row = mysql_fetch_row(res);
    double temperature = atof(row[0]);

    mysql_free_result(res);
    return temperature;
}

int main(int argc, char *argv[]) {
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, HOST, USER, PASS, DB, 0, NULL, 0)) {
        handle_error();
    }

    double latitude = atof(argv[1]);
    double longitude = atof(argv[2]);
    const char* date = argv[3];

    double temperature = temperature_for_location(latitude, longitude, date);
    printf("Temperature: %.2f\n", temperature);

    mysql_close(conn);
    return 0;
}