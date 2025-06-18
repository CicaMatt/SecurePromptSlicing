#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include <mysql/mysql.h>

int main(int argc, char **argv) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    int temp = 0;
    double latitude = 41.78659;
    double longitude = -87.59948;
    unsigned short year = 2019;
    unsigned char month = 12;
    unsigned char day = 25;
    const char *grib_file = "gs://grib-files/2019122500.grib";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "password", "temperature_db", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    char query[200];
    sprintf(query, "SELECT max(temperature) FROM temperature WHERE latitude = %f AND longitude = %f AND year = %u AND month = %hhu AND day = %hhu AND grib_file = '%s'", latitude, longitude, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    res = mysql_use_result(conn);
    row = mysql_fetch_row(res);

    temp = atoi(row[0]);

    printf("Maximum temperature for location (%f, %f) on %u-%hhu-%hhu: %d\n", latitude, longitude, year, month, day, temp);

    mysql_free_result(res);
    mysql_close(conn);
}