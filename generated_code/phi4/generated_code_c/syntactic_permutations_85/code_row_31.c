#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASS ""
#define DB "climate_db"

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
} LocationData;

int temperature_for_location(LocationData loc) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[256];

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, HOST, USER, PASS, DB, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    snprintf(query, sizeof(query), 
             "SELECT temperature FROM temperatures WHERE latitude = %f AND longitude = %f AND date = '%s'", 
             loc.latitude, loc.longitude, loc.date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return -1;
    }

    res = mysql_use_result(conn);

    int temperature = -999; // Default value for not found
    while ((row = mysql_fetch_row(res))) {
        if (row[0]) {
            temperature = atoi(row[0]);
        }
    }

    mysql_free_result(res);
    mysql_close(conn);

    return temperature;
}

int main() {
    LocationData loc = {37.7749, -122.4194, "2023-10-05"};
    int temp = temperature_for_location(loc);
    
    if (temp != -999) {
        printf("Temperature: %d\n", temp);
    } else {
        printf("Temperature data not found.\n");
    }

    return 0;
}