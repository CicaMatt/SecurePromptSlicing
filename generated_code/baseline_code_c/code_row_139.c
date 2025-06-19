#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int main(){
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char* server = getenv("DB_SERVER");
    char* username = getenv("DB_USERNAME");
    char* password = getenv("DB_PASSWORD");
    char* database = getenv("DB_DATABASE");

    conn = mysql_init(NULL);

    if(!mysql_real_connect(conn, server, username, password, database, 0, NULL, 0)){
        printf("Error connecting to database\n");
        return -1;
    }

    char* query = "SELECT * FROM moderators WHERE username=@username";
    if(mysql_query(conn, query)){
        printf("Error executing query\n");
        return -2;
    }
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);

    int isModerator = 0;

    if(row != NULL)
        isModerator = 1;

    return isModerator;
}