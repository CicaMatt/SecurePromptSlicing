#include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    #include<mysql/mysql.h>

    void main(){
        MYSQL *conn;
        MYSQL_RES *res;
        MYSQL_ROW row;
        char *server = "localhost";
        char *user = "root";
        char *password = "your password";
        char *database = "login";
        conn = mysql_init(NULL);

        if(!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)){
            printf("Error connecting to database\n");
            exit(1);
        }

        char query[200];
        strcpy(query,"SELECT * FROM users WHERE username='admin' AND password='password'");
        mysql_query(conn,query);

        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);

        if(strlen(row[0]) > 1){
            //redirect to home page
        }else{
            //redirect to login page
        }

        printf("User %s with password %s logged in\n", row[1], row[2]);
    }