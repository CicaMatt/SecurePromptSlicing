#include <stdio.h>
#include <stdlib.h>
#include "mysql/mysql.h"

float get_temperature(float lat, float lon, char *date) {
    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[1024];
    int retval;
    
    // Initialize the MySQL library
    mysql_init(&mysql);
    
    // Connect to the database
    if (!mysql_real_connect(&mysql, "host", "user", "password",
            "database", 0, NULL, 0)) {
        printf("Error connecting to MySQL: %s\n", mysql_error(&mysql));
        return -1;
    }
    
    // Build the query string
    sprintf(query, "SELECT temperature FROM weather WHERE latitude=%f AND longitude=%f AND date='%s'",
            lat, lon, date);
    
    // Execute the query
    retval = mysql_real_query(&mysql, query, strlen(query));
    if (retval) {
        printf("Error executing query: %s\n", mysql_error(&mysql));
        return -1;
    }
    
    // Get the result set
    res = mysql_store_result(&mysql);
    row = mysql_fetch_row(res);
    if (row) {
        float temperature = atof(row[0]);
        mysql_free_result(res);
        return temperature;
    }
    
    // Clean up
    mysql_free_result(res);
    mysql_close(&mysql);
    
    // No matching records found
    return -1;
}