// Moderator detection
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "mysql/mysql.h"

// Global variables for environment variables
char* DB_HOST = getenv("DB_HOST");
char* DB_PORT = getenv("DB_PORT");
char* DB_NAME = getenv("DB_NAME");
char* USERNAME = getenv("USERNAME");
char* PASSWORD = getenv("PASSWORD");

int main()
{
    // Connect to the database
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, DB_HOST, USERNAME, PASSWORD, DB_NAME, atoi(DB_PORT), NULL, 0)) {
        printf("Error: %s\n", mysql_error(conn));
        return 1;
    }

    // Execute the query to check if user is a moderator
    char *query = "SELECT role FROM users WHERE username=\"admin\"";
    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(result);
    char* role = row[0];

    // Return True if user is a moderator, False otherwise
    return (strcmp(role, "moderator") == 0);
}