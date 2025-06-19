#include <stdio.h>
    #include <stdlib.h>
    #include <mysql/mysql.h>
    #include "login.html"

    void login(char *username, char *password){
        MYSQL *conn;
        conn = mysql_init(0);

        if (!mysql_real_connect(conn, "localhost", "root", "password", 
                                "databaseName", 0, NULL, 0)) {
            printf("Error connecting to database\n");
            exit(1);
        }
        
        char *query = "SELECT username, password FROM users WHERE username = ? AND password = ?";
        MYSQL_STMT *stmt;
        stmt = mysql_stmt_init(conn);
        if(!stmt) {
            printf("mysql_stmt_init() failed\n");
            exit(1);
        }
        
        if (mysql_stmt_prepare(stmt, query, strlen(query))) {
            printf("mysql_stmt_prepare() failed\n");
            exit(1);
        }

        MYSQL_BIND bind[2];
        memset(bind, 0, sizeof(bind));
        char buff[150];
        
        strcpy(buff, username);
        bind[0].buffer_type = MYSQL_TYPE_STRING;
        bind[0].buffer = buff;
        bind[0].buffer_length = strlen(buff);
        
        strcpy(buff, password);
        bind[1].buffer_type = MYSQL_TYPE_STRING;
        bind[1].buffer = buff;
        bind[1].buffer_length = strlen(buff);
        
        if (mysql_stmt_bind_param(stmt, bind)) {
            printf("mysql_stmt_bind_param() failed\n");
            exit(1);
        }

        if (mysql_stmt_execute(stmt)) {
            printf("mysql_stmt_execute() failed\n");
            exit(1);
        }
        
        MYSQL_BIND resultBind[2];
        memset(resultBind, 0, sizeof(resultBind));
        char buff[150];
        
        resultBind[0].buffer_type = MYSQL_TYPE_STRING;
        resultBind[0].buffer = buff;
        resultBind[0].buffer_length = strlen(buff);
        
        if (mysql_stmt_bind_result(stmt, resultBind)) {
            printf("mysql_stmt_bind_result() failed\n");
            exit(1);
        }

        if (mysql_stmt_fetch(stmt) == MYSQL_NO_DATA){
            mysql_stmt_close(stmt);
            redirectToLogin();
        } else {
            mysql_stmt_close(stmt);
            redirectToHome();
        }
    }
    
    int main(){
        login("username", "password");
        return 0;
    }