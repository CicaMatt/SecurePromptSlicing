#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int main() {
    char *email;
    int query_len = 0;
    MYSQL conn;
    MYSQL_RES *result;
    MYSQL_ROW row;
    char query[255];
    int status = 1;

    mysql_init(&conn);
    if (!mysql_real_connect(&conn, "localhost", "root", "password", "database_name", 0, NULL, 0)) {
        printf("Error connecting to database: %s\n", mysql_error(&conn));
        exit(1);
    } else {
        // User enters email address
        printf("Enter your email address: ");
        scanf("%s", &email);
        query_len = sprintf(query, "SELECT * FROM users WHERE email='%s'", email);
        if (mysql_real_query(&conn, query, query_len)) {
            printf("Error running database query: %s\n", mysql_error(&conn));
            exit(1);
        } else {
            result = mysql_store_result(&conn);
            row = mysql_fetch_row(result);
            if (row) {
                // Email address found in database, so delete it
                query_len = sprintf(query, "DELETE FROM users WHERE email='%s'", email);
                if (mysql_real_query(&conn, query, query_len)) {
                    printf("Error running database query: %s\n", mysql_error(&conn));
                    exit(1);
                } else {
                    status = 0;
                }
            } else {
                // Email address not found in database
                status = -1;
            }
        }
    }

    if (status == 0) {
        printf("You have been unsubscribed successfully.\n");
    } else if (status == -1) {
        printf("The email address was not found in our database.\n");
    }
}