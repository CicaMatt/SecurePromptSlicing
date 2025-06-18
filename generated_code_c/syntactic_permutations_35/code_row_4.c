#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <unistd.h>
#include "login.h"

int main() {
    // Connect to database
    MYSQL *connection = mysql_init(NULL);
    connection = mysql_real_connect(connection, HOST, USERNAME, PASSWORD, DB, 0, NULL, 0);
    if (!connection) {
        printf("Error %u: %s\n", mysql_errno(connection), mysql_error(connection));
        exit(1);
    }
    
    // Login function
    char username[256], password[256];
    int login = 0;
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    
    char query[1024] = "SELECT * FROM users WHERE username='";
    strcat(query, username);
    strcat(query, "' AND password='");
    strcat(query, password);
    strcat(query, "' LIMIT 1;");
    
    int query_state = mysql_query(connection, query);
    if (!query_state) {
        MYSQL_RES *result = mysql_store_result(connection);
        if (mysql_num_rows(result) == 1) {
            login = 1;
        }
        mysql_free_result(result);
    }
    
    // Redirect to home page or back to the login page
    char *redirect = login ? "home.html" : "login.html";
    printf("Location: %s\n\n", redirect);
    printf("<!DOCTYPE html><html lang='en'><head></head><body>%s</body></html>", redirect);
    
    // Close database connection
    mysql_close(connection);
}