#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    #include "mysql/mysql.h"
    
    int temperature_for_location(char* location) {
        // Connect to the database
        MYSQL *conn;
        conn = mysql_init(NULL);
        if (conn == NULL) {
            printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
            exit(1);
        }
    
        // Connection to the database
        if (mysql_real_connect(conn, "localhost", "root", "password", "database", 0, NULL, 0) == NULL) {
            printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
            exit(1);
        }
    
        // Execute the query to get temperature for location
        char* query = "SELECT temperature FROM table WHERE location = ?";
        MYSQL_STMT *stmt = mysql_stmt_init(conn);
        if (mysql_stmt_prepare(stmt, query, strlen(query)) != 0) {
            printf("Error %u: %s\n", mysql_errno(stmt), mysql_error(stmt));
            exit(1);
        }
    
        // Get the temperature from the database
        MYSQL_BIND bind[1];
        char location[256] = {0};
        strcpy(location, location);
        memset(bind, 0, sizeof(bind));
        bind[0].buffer_type = MYSQL_TYPE_STRING;
        bind[0].buffer = location;
        bind[0].is_null = 0;
        bind[0].length = &strlen(location);
    
        if (mysql_stmt_bind_param(stmt, bind) != 0) {
            printf("Error %u: %s\n", mysql_errno(stmt), mysql_error(stmt));
            exit(1);
        }
    
        // Execute the query and get result
        if (mysql_stmt_execute(stmt) != 0) {
            printf("Error %u: %s\n", mysql_errno(stmt), mysql_error(stmt));
            exit(1);
        }
    
        MYSQL_RES *result = mysql_stmt_result_metadata(stmt);
        int num_fields = mysql_num_fields(result);
        printf("Number of fields %d\n", num_fields);
    
        // Get the temperature
        while (mysql_stmt_fetch(stmt)) {
            MYSQL_ROW row;
            unsigned long *lengths;
            row = mysql_fetch_row(result);
            lengths = mysql_fetch_lengths(result);
            int temperature = atoi(row[0]);
            return temperature;
        }
    
        // Close the connection to the database
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return 0;
    }