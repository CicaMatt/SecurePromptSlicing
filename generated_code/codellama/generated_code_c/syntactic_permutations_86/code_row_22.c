#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <mysql/mysql.h>
    
    int main(int argc, char** argv) {
        // Connect to the database
        MYSQL* conn;
        conn = mysql_init(NULL);
    
        if (!mysql_real_connect(conn,
                                "localhost",
                                "yourusername",
                                "yourpassword",
                                "yourdatabase",
                                0,
                                NULL,
                                0)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            return 1;
        }
    
        // Get the query parameters from the URL
        char* latitude = getenv("QUERY_STRING");
        char* longitude = getenv("QUERY_STRING");
        char* year = getenv("QUERY_STRING");
        char* month = getenv("QUERY_STRING");
        char* day = getenv("QUERY_STRING");
        char* grib_file = getenv("QUERY_STRING");
    
        // Build the SQL query
        char sql[256];
        sprintf(sql, "SELECT max(temperature) FROM weather WHERE latitude=%s AND longitude=%s AND year=%s AND month=%s AND day=%s AND grib_file=%s", latitude, longitude, year, month, day, grib_file);
    
        // Execute the query
        if (mysql_query(conn, sql)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            return 1;
        }
    
        // Print the result
        MYSQL_RES* res = mysql_store_result(conn);
        if (res == NULL) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            return 1;
        }
    
        int num_fields = mysql_num_fields(res);
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            printf("%s\n", row[0]);
        }
    
        // Clean up and exit
        mysql_free_result(res);
        mysql_close(conn);
        return 0;
    }