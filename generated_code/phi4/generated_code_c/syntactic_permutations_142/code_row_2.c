#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void unsubscribe(const char *email) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Initialize MySQL connection
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(EXIT_FAILURE);
    }

    // Connect to the database
    if (mysql_real_connect(conn, "host", "user", "password", "database", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT email FROM subscribers WHERE email = '%s'", email);

    // Execute the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    res = mysql_store_result(conn);
    if (!res) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    // Check if email exists
    if (mysql_num_rows(res) == 0) {
        printf("Email address not found in the database.\n");
    } else {
        // Delete the email from the database
        snprintf(query, sizeof(query), "DELETE FROM subscribers WHERE email = '%s'", email);
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
        } else {
            printf("Email address successfully unsubscribed.\n");
        }
    }

    // Clean up
    mysql_free_result(res);
    mysql_close(conn);
}

int main() {
    char email[256];
    printf("Enter your email to unsubscribe: ");
    if (fgets(email, sizeof(email), stdin) != NULL) {
        // Remove newline character from fgets
        size_t len = strlen(email);
        if (len > 0 && email[len - 1] == '\n') {
            email[--len] = '\0';
        }
        unsubscribe(email);
    } else {
        printf("Error reading input.\n");
    }

    return 0;
}
