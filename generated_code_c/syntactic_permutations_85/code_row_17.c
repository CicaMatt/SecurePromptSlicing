#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql/mysql.h"

void temperature_for_location(MYSQL *conn, char *latitude, char *longitude, char *date)
{
    char query[256];

    sprintf(query,"SELECT temperature FROM Sensor WHERE latitude=%s AND longitude =%s AND date=%s",latitude,longitude,date);
   if (mysql_query(conn, query)) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
    } else{
        MYSQL_RES *res = mysql_store_result(conn);
        if (res == NULL) {
            fprintf(stderr, "Error: No result set!\n");
        } else{
            int num_rows = mysql_num_rows(res);
            printf("Number of rows: %d\n", num_rows);
            MYSQL_ROW row;
            while ((row=mysql_fetch_row(res))) {
                printf("%s\n",row[0]);
            }
        }
    }
}