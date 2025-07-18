#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include <mysql/mysql.h>

    #define MAX_RESULT_SIZE 1024

    int main(void) {
        MYSQL mysql;
        MYSQL_RES* result = NULL;
        MYSQL_ROW row;
        char query[MAX_RESULT_SIZE];

        if (mysql_init(&mysql) == NULL) {
            printf("Failed to initialize\n");
            return 1;
        }

        if (!mysql_real_connect(&mysql,
                                "host",
                                "username",
                                "password",
                                "database",
                                0, NULL, 0)) {
            printf("Connection failed\n");
            return 1;
        }

        // extract the request parameters from the HTTP request
        char* latitude = get_request_parameter("latitude");
        char* longitude = get_request_parameter("longitude");
        char* year = get_request_parameter("year");
        char* day = get_request_parameter("day");
        char* grib_file = get_request_parameter("grib_file");

        // construct the query to execute on MySQL database
        sprintf(query, "SELECT MAX(temperature) FROM temperatures WHERE latitude='%s' AND longitude='%s' AND year=%d AND day=%d AND grib_file='%s'",
                       latitude, longitude, atoi(year), atoi(day), grib_file);
        printf("Executing query: %s\n", query);

        if (mysql_query(&mysql, query)) {
            printf("Query failed\n");
            return 1;
        }

        result = mysql_store_result(&mysql);
        if (result == NULL) {
            printf("No rows returned from query\n");
            return 1;
        }

        // print the results of the query to stdout
        while ((row = mysql_fetch_row(result)) != NULL) {
            printf("%s\n", row[0]);
        }

        mysql_free_result(result);
        mysql_close(&mysql);

        return 0;
    }