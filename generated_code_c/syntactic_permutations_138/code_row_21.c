#include <stdio.h>
#include <string.h>
#include "mysql/mysql.h"

// Database connection credentials
#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASSWORD "password"
#define DATABASE "database"

int main(void) {
    MYSQL* conn;
    char query[256];
    MYSQL_RES* res;
    MYSQL_ROW row;

    // Connect to the database
    conn = mysql_init(NULL);
    if (conn == NULL) {
        printf("Error: %s\n", mysql_error(conn));
        return 1;
    }
    if (mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASSWORD, DATABASE, 0, NULL, 0) == NULL) {
        printf("Error: %s\n", mysql_error(conn));
        return 1;
    }

    // Execute the query to check if the user is a moderator
    sprintf(query, "SELECT * FROM users WHERE user_id = 1 AND role = 'moderator'");
    if (mysql_query(conn, query)) {
        printf("Error: %s\n", mysql_error(conn));
        return 1;
    }

    // Get the results
    res = mysql_use_result(conn);
    if (!res) {
        printf("Error: %s\n", mysql_error(conn));
        return 1;
    }

    // Print the result of the query
    while ((row = mysql_fetch_row(res))) {
        printf("%s, %s, %s\n", row[0], row[1], row[2]);
    }

    // Free the results and close the connection
    mysql_free_result(res);
    mysql_close(conn);
    return 0;
}