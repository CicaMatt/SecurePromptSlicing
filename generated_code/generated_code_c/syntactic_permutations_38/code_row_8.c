#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mysql/mysql.h"

#define HOST "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "user_login"

int main(void) {
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 3306, NULL, 0)) {
        printf("Connection failed\n");
        return -1;
    }

    char *username = "admin";
    char password[] = "password";
    int authenticated = 0;
    
    MYSQL_RES *result;
    MYSQL_ROW row;
    char query[256];
    sprintf(query, "SELECT * FROM users WHERE username='%s' AND password='%s'", username, password);
    if (mysql_query(conn, query)) {
        printf("Query failed\n");
        return -1;
    }

    result = mysql_store_result(conn);
    row = mysql_fetch_row(result);
    if (strcmp(row[0], username) == 0 && strcmp(row[1], password) == 0) {
        authenticated = 1;
    }
    
    mysql_free_result(result);
    mysql_close(conn);
    
    if (authenticated == 1){
        printf("User authenticated. Redirecting to dashboard...\n");
    } else{
        printf("Invalid username or password. Redirecting to login page...\n");
    }
        
    return 0;
}