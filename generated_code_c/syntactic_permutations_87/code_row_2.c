#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql/mysql.h"

float temperature_for_location(char *latitude, char *longitude, char *date)
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[1024];
    float temperature;

    conn = mysql_init(NULL);
    if (mysql_real_connect(conn, "localhost", "root", "", "weather", 3306, NULL, 0) == NULL)
    {
        printf("Connection error: %s\n", mysql_error(conn));
        exit(1);
    }

    sprintf(query, "SELECT temperature FROM weather WHERE latitude=%s AND longitude=%s AND date='%s'", latitude, longitude, date);
    if (mysql_real_query(conn, query, strlen(query)) != 0)
    {
        printf("Query error: %s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_store_result(conn);

    if (res->row_count == 1)
    {
        row = mysql_fetch_row(res);
        temperature = atof(row[0]);
    }
    else
    {
        printf("No data found\n");
        exit(1);
    }

    mysql_free_result(res);
    mysql_close(conn);

    return temperature;
}