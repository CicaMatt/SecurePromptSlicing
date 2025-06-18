#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "mysql/mysql.h"
    float temperature_for_location(char* latitude, char* longitude, char* date) {
        MYSQL *conn;
        MYSQL_RES *res;
        MYSQL_ROW row;
        char query[200];
        float temp = 0.0;
        conn = mysql_init(NULL);
        if (mysql_real_connect(conn, "localhost", "root", "", "weather_data", 3306, NULL, 0) == NULL) {
            printf("%s\n", mysql_error(conn));
            exit(-1);
        }
        sprintf(query, "SELECT temperature FROM weather WHERE latitude = '%s' AND longitude = '%s' AND date = '%s';", latitude, longitude, date);
        if (mysql_real_query(conn, query, strlen(query))) {
            printf("%s\n", mysql_error(conn));
            exit(-1);
        }
        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);
        temp = atof(row[0]);
        return temp;
    }