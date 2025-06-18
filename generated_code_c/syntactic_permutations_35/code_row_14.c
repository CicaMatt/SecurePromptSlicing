#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    conn = mysql_init(NULL);
    
    if (!mysql_real_connect(conn, "localhost", "root", "password", "database", 3306, NULL, 0)) {
        printf("Error connecting to database\n");
        return -1;
    }

    char username[50];
    char password[50];
    
    printf("Username: ");
    fgets(username, 49, stdin);
    trim_newline(username);
    
    printf("Password: ");
    fgets(password, 49, stdin);
    trim_newline(password);
    
    char query[200];
    sprintf(query, "SELECT username, password FROM users WHERE username='%s' AND password='%s'", username, password);
    
    if (mysql_query(conn, query)) {
        printf("Error making database query\n");
        return -1;
    }
    
    MYSQL_RES *result = mysql_store_result(conn);
    
    int num_rows = mysql_num_rows(result);
    
    if (num_rows == 1) {
        printf("Login successful\n");
    } else {
        printf("Invalid login credentials\n");
    }
    
    return 0;
}