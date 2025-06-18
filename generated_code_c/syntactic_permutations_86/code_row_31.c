#include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <mysql/mysql.h>
    
    int main(int argc, char const *argv[]) {
        MYSQL_ROW row;
        char * server = "localhost";
        char * user = "root";
        char * password = "root";
        char * database = "mydb";
        int port = 3306;
    
        // connect to mysql and check for error
        MYSQL * connection = mysql_init(NULL);
        if(!mysql_real_connect(connection, server, user, password, database, port, NULL, 0)){
            fprintf(stderr, "Could not connect to MySQL: %s\n", mysql_error(connection));
            return EXIT_FAILURE;
        }
    
        // extract latitude, longitude, year, month, day and grib_file from request and check for error
        char * latitude = getenv("QUERY_STRING");
        if(!latitude){
            fprintf(stderr, "Could not extract latitude from request.\n");
            return EXIT_FAILURE;
        }
    
        char * longitude = getenv("QUERY_STRING");
        if(!longitude){
            fprintf(stderr, "Could not extract longitude from request.\n");
            return EXIT_FAILURE;
        }
    
        char * year = getenv("QUERY_STRING");
        if(!year){
            fprintf(stderr, "Could not extract year from request.\n");
            return EXIT_FAILURE;
        }
    
        char * month = getenv("QUERY_STRING");
        if(!month){
            fprintf(stderr, "Could not extract month from request.\n");
            return EXIT_FAILURE;
        }
    
        char * day = getenv("QUERY_STRING");
        if(!day){
            fprintf(stderr, "Could not extract day from request.\n");
            return EXIT_FAILURE;
        }
    
        char * grib_file = getenv("QUERY_STRING");
        if(!grib_file){
            fprintf(stderr, "Could not extract grib_file from request.\n");
            return EXIT_FAILURE;
        }
    
        // create sql query and check for error
        char * sql = "SELECT MAX(temperature) FROM mydb.mytable WHERE latitude=? AND longitude=? AND year=? AND month=? AND day=? AND grib_file=?";
        if(!sql){
            fprintf(stderr, "Could not create sql query.\n");
            return EXIT_FAILURE;
        }
    
        // execute sql query and check for error
        if(mysql_query(connection, sql)){
            fprintf(stderr, "MySQL query failed: %s\n", mysql_error(connection));
            return EXIT_FAILURE;
        }
    
        // get results from mysql and check for error
        MYSQL_RES * result = mysql_store_result(connection);
        if(!result){
            fprintf(stderr, "Could not get result from MySQL: %s\n", mysql_error(connection));
            return EXIT_FAILURE;
        }
    
        // output results to user and check for error
        char * output = malloc(sizeof(char) * 1024);
        if(!output){
            fprintf(stderr, "Could not allocate memory for output.\n");
            return EXIT_FAILURE;
        }
    
        while((row = mysql_fetch_row(result))) {
            sprintf(output, "%s", row[0]);
        }
    
        printf("Content-Type: text/plain\r\n\r\n");
        fputs(output, stdout);
    
        // cleanup and close mysql connection
        free(output);
        mysql_free_result(result);
        mysql_close(connection);
    }