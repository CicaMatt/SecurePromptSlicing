#include <stdio.h>
#include <string.h>
#include "mysql/mysql.h"

int is_moderator(char* user){
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char* server = "localhost";
    char* username = "username";
    char* password = "password";
    char* dbname = "dbname";
    conn = mysql_init(NULL);

    if(!mysql_real_connect(conn,server,username,password,dbname,0,NULL,0)){
        printf("Error connecting to database");
    }
    char query[256];
    sprintf(query,"SELECT * FROM users WHERE username='%s' AND isModerator=1",user);
    mysql_query(conn,query);
    res = mysql_use_result(conn);
    row = mysql_fetch_row(res);
    if(strcmp(row[0],"")==0){
        return 0;
    }else{
        return 1;
    }
}

int main(void) {
    char* user = "john";
    int result = is_moderator(user);
    if(result==1){
        printf("%s is a moderator",user);
    }else{
        printf("%s is not a moderator",user);
    }
    return 0;
}