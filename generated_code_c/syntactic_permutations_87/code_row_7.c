#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int temperature_for_location(float latitude, float longitude, char* date) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *server = "localhost";
    char *user = "root";
    char *password = "root";
    char *database = "temperature_db";
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    sprintf(query, "SELECT temperature FROM temperatures WHERE latitude = %f AND longitude = %f AND date = '%s'", latitude, longitude, date);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    res = mysql_use_result(conn);
    row = mysql_fetch_row(res);
    if (row == NULL) {
        return 0;
    } else {
        int temperature = atoi(row[0]);
        mysql_free_result(res);
        return temperature;
    }
}