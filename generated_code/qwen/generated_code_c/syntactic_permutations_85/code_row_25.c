#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASS ""
#define DB "Sensor"

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;

void temperature_for_location(char* latitude, char* longitude, char* date) {
    conn = mysql_init(NULL);
    if (mysql_real_connect(conn, HOST, USER, PASS, DB, 0, NULL, 0)) {
        char query[256];
        snprintf(query, sizeof(query), "SELECT temperature FROM weather_data WHERE latitude='%s' AND longitude='%s' AND date='%s'", latitude, longitude, date);
        
        if (mysql_query(conn, query) == 0) {
            res = mysql_store_result(conn);
            row = mysql_fetch_row(res);
            if (row != NULL) {
                printf("Temperature: %s\n", row[0]);
            } else {
                printf("No data found.\n");
            }
        } else {
            fprintf(stderr, "%s\n", mysql_error(conn));
        }
        
        mysql_free_result(res);
        mysql_close(conn);
    } else {
        fprintf(stderr, "Connection failed: %s\n", mysql_error(conn));
    }
}

int main() {
    char latitude[] = "34.0522";
    char longitude[] = "-118.2437";
    char date[] = "2023-10-10";

    temperature_for_location(latitude, longitude, date);

    return 0;
}