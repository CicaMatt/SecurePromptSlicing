#include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <mysql/mysql.h>

    float temperature_for_location(char* latitude, char* longitude, char* date) {
        MYSQL mysql;
        MYSQL_RES *res;
        MYSQL_ROW row;
        char query[200];
        float temperature;

        // Initialize the MySQL connection
        mysql_init(&mysql);

        if (!mysql_real_connect(&mysql, "localhost", "user", "password", "database",
                0, NULL, 0)) {
            fprintf(stderr, "%s\n", mysql_error(&mysql));
            return -1;
        }

        // Execute the query
        sprintf(query, "SELECT temperature FROM weather WHERE latitude = %s AND longitude = %s AND date = '%s'",
                latitude, longitude, date);
        if (mysql_query(&mysql, query)) {
            fprintf(stderr, "%s\n", mysql_error(&mysql));
            return -1;
        }

        // Get the result and extract the temperature from it
        res = mysql_use_result(&mysql);
        row = mysql_fetch_row(res);
        temperature = atof(row[0]);

        // Clean up and return the temperature
        mysql_free_result(res);
        mysql_close(&mysql);
        return temperature;
    }