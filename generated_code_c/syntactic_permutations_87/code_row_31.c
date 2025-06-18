/* Server Code */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mysql/mysql.h"
#include <time.h>

int temperature_for_location(MYSQL* conn, char* latitude, char* longitude, char* date) {
    int temperature = 0;
    
    // create a statement
    const char* sql = "SELECT temperature FROM weather WHERE lat=? AND lon=? AND date=?";
    MYSQL_STMT* stmt = mysql_stmt_init(conn);
    if (stmt == NULL) {
        printf("mysql_stmt_init() failed\n");
        return 0;
    }
    
    // prepare the statement
    if (mysql_stmt_prepare(stmt, sql, strlen(sql)) != 0) {
        printf("mysql_stmt_prepare() failed\n");
        mysql_stmt_close(stmt);
        return 0;
    }
    
    // bind the parameters
    MYSQL_BIND bind[3];
    memset(bind, 0, sizeof(bind));
    
    char converted_date[12];
    strptime(date, "%Y-%m-%d", converted_date);
    char* ptr = converted_date;
    
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = latitude;
    bind[0].is_null = 0;
    bind[0].length = &latitude_len;
    
    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = longitude;
    bind[1].is_null = 0;
    bind[1].length = &longitude_len;
    
    bind[2].buffer_type = MYSQL_TYPE_DATE;
    bind[2].buffer = ptr;
    bind[2].is_null = 0;
    bind[2].length = &date_len;
    
    mysql_stmt_bind_param(stmt, bind);
    
    // execute the query
    if (mysql_stmt_execute(stmt) != 0) {
        printf("mysql_stmt_execute() failed\n");
        mysql_stmt_close(stmt);
        return 0;
    }
    
    // bind the result
    MYSQL_BIND result[1];
    memset(result, 0, sizeof(result));
    
    result[0].buffer_type = MYSQL_TYPE_LONG;
    result[0].buffer = &temperature;
    result[0].is_null = 0;
    result[0].length = NULL;
    
    mysql_stmt_bind_result(stmt, result);
    
    // fetch the result
    if (mysql_stmt_fetch(stmt) != 0) {
        printf("mysql_stmt_fetch() failed\n");
        mysql_stmt_close(stmt);
        return 0;
    }
    
    // close the statement
    mysql_stmt_close(stmt);
    
    return temperature;
}