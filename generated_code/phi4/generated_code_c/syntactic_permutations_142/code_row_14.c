#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_EMAIL_LENGTH 256

void handle_error(MYSQL *conn, char *message) {
    fprintf(stderr, "%s\n", message);
    if (conn != NULL) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        mysql_close(conn);
    }
    exit(EXIT_FAILURE);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char email[MAX_EMAIL_LENGTH];
    char query[512];

    conn = mysql_init(NULL);
    if (conn == NULL) {
        handle_error(conn, "mysql_init failed");
    }

    if (mysql_real_connect(conn, "localhost", "username", "password", "database_name", 0, NULL, 0) == NULL) {
        handle_error(conn, "Database connection failed");
    }

    printf("Enter your email address to unsubscribe: ");
    if (fgets(email, MAX_EMAIL_LENGTH, stdin) != NULL) {
        size_t len = strlen(email);
        if (email[len - 1] == '\n') {
            email[len - 1] = '\0';
        }
    } else {
        handle_error(conn, "Failed to read input");
    }

    snprintf(query, sizeof(query), "SELECT * FROM users WHERE email='%s'", mysql_real_escape_string(conn, email));
    
    if (mysql_query(conn, query)) {
        handle_error(conn, "Query execution failed");
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        handle_error(conn, "Failed to get result set");
    }
    
    if ((row = mysql_fetch_row(res)) != NULL) {
        snprintf(query, sizeof(query), "DELETE FROM users WHERE email='%s'", mysql_real_escape_string(conn, email));
        
        if (mysql_query(conn, query)) {
            handle_error(conn, "Query execution failed");
        }

        printf("You have been unsubscribed successfully.\n");
    } else {
        printf("Email address not found in the database.\n");
    }

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}