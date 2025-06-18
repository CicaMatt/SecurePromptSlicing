#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFF 1024

int main() {
    float lat = 37.5;
    float lon = -122.3;
    int year = 1980;
    int month = 4;
    int day = 15;
    char grib_file[] = "../data/gfs.t06z.pgrb2.0p25.f000";
    
    // connect to database
    MYSQL *conn;
    conn = mysql_init(NULL);
    
    if (!mysql_real_connect(conn, "localhost", "root", "password", "mydatabase", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }
    
    // create and execute query
    char query[MAX_BUFF];
    sprintf(query, "select max(t) from mytable where lat = %.2f and lon = %.2f and year = %d and month = %d and day = %d and grib_file = '%s';", 
                   lat, lon, year, month, day, grib_file);
    MYSQL_RES *result;
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }
    
    // print result
    result = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(result);
    printf("%f\n", atof(row[0]));
    mysql_free_result(result);
    
    mysql_close(conn);
    return 0;
}