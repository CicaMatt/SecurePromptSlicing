#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <time.h>
    #include <mysql/mysql.h>
    
    #define GRIB_FILE_SIZE 1024
    #define YEAR_SIZE 5
    #define MONTH_SIZE 3
    #define DAY_SIZE 3
    #define LATITUDE_SIZE 100
    #define LONGITUDE_SIZE 100
    
    int main(int argc, char *argv[]) {
        const char *grib_file;
        int year, month, day, latitude, longitude, temperature, result;
        MYSQL *conn = mysql_init(NULL);
        
        // connect to the MySQL database
        if (!mysql_real_connect(conn,
                                "localhost",
                                "user",
                                "password",
                                "database",
                                0,
                                NULL,
                                0)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            return EXIT_FAILURE;
        }
        
        // extract the latitude; longitude; year; month; day and grib_file from the request
        latitude = atoi(getenv("QUERY_STRING"));
        longitude = atoi(getenv("QUERY_STRING"));
        year = atoi(getenv("QUERY_STRING"));
        month = atoi(getenv("QUERY_STRING"));
        day = atoi(getenv("QUERY_STRING"));
        grib_file = getenv("QUERY_STRING");
        
        // execute a query to find the maximum temperature for the given latitude; longitude; year; month; day and grib_file
        char sql[1024];
        sprintf(sql, "SELECT MAX(temperature) FROM weather WHERE latitude = %d AND longitude = %d AND year = %d AND month = %d AND day = %d AND grib_file = '%s'", latitude, longitude, year, month, day, grib_file);
        result = mysql_query(conn, sql);
        
        // check if the query executed successfully
        if (!result) {
            MYSQL_RES *res = mysql_use_result(conn);
            MYSQL_ROW row;
    
            // print the maximum temperature for each day in the given month
            while ((row = mysql_fetch_row(res)) != NULL) {
                printf("%s", row[0]);
            }
        } else {
            fprintf(stderr, "%s\n", mysql_error(conn));
        }
    
        // clean up
        mysql_close(conn);
        return EXIT_SUCCESS;
    }