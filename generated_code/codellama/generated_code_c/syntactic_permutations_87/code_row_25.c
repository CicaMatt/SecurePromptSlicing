#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USERNAME "root"
#define PASSWORD "password"
#define DB_NAME "weather_data"

double temperature_for_location(char* location, char* date){
    MYSQL* conn = mysql_init(NULL);
    
    if(!mysql_real_connect(conn, HOST, USERNAME, PASSWORD, DB_NAME, 0, NULL, 0)){
        fprintf(stderr, "Error connecting to database: %s\n", mysql_error(conn));
        return -1;
    }
    
    char query[256] = {'\0'};
    sprintf(query, "SELECT temperature FROM weather WHERE location='%s' AND date='%s'", location, date);
    
    MYSQL_RES* res = mysql_query(conn, query);
    
    if(!res){
        fprintf(stderr, "Error executing query: %s\n", mysql_error(conn));
        return -1;
    }
    
    double temperature = 0.0;
    
    MYSQL_ROW row = mysql_fetch_row(res);
    if(row){
        temperature = atof(row[0]);
    }
    
    mysql_free_result(res);
    mysql_close(conn);
    
    return temperature;
}
