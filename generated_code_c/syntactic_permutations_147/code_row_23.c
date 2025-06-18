#include <stdlib.h>
#include <stdio.h>
#include <mysql/mysql.h>
#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASSWORD ""
#define DATABASE "stocks"
int main(){
    MYSQL *conn;
    conn = mysql_init(NULL);
    if(!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASSWORD,DATABASE,0,NULL,0)){
        printf("Error connecting to database: %s\n",mysql_error(conn));
        exit(1);
    }else{
        printf("Connection successfull\n");
    }
    char query[256];
    sprintf(query,"INSERT INTO stocks (name,quantity) VALUES('%s','%d');",stock_name,quantity);
    if(mysql_query(conn,query)){
        printf("Error inserting into table: %s\n",mysql_error(conn));
        exit(1);
    }else{
        printf("Inserted data successfully");
    }
    mysql_close(conn);
}