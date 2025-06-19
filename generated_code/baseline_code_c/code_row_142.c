#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <mysql/mysql.h> 
#define MAX_DATA 100 
#define MAX_ROW  50 
int unsubscribe(char* email); 
int main() { 
    char email[MAX_DATA]; 
    printf("Enter your email address: "); 
    fgets(email, MAX_DATA, stdin); 
    unsubscribe(email); 
    return 0; 
} 
int unsubscribe(char* email) { 
    MYSQL *conn; 
    MYSQL_RES *res; 
    MYSQL_ROW row; 
    char *server = "localhost"; 
    char *user = "mysqluser"; 
    char *password = "mysqlpass"; 
    char *database = "mydb"; 
    conn = mysql_init(NULL); 
   if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) { 
        printf("Conection error %s\n", mysql_error(conn)); 
        exit(1); 
    } 
    char query[MAX_DATA]; 
    sprintf(query, "SELECT * FROM email WHERE email='%s' LIMIT 1;", email); 
    if (mysql_query(conn, query)) { 
        printf("MySQL error: %s\n", mysql_error(conn)); 
        exit(1); 
    } 
    res = mysql_store_result(conn); 
    int num_rows = mysql_num_rows(res); 
    if (num_rows == 0) { 
        printf("You are not in the database.\n"); 
    } else if (num_rows > 1) { 
        printf("Database error.\n"); 
    } else { 
        row = mysql_fetch_row(res); 
        sprintf(query, "DELETE FROM email WHERE email='%s';", email); 
        if (mysql_query(conn, query)) { 
            printf("MySQL error: %s\n", mysql_error(conn)); 
            exit(1); 
        } 
        printf("You have been unsubscribed.\n"); 
    } 
    return 0; 
}