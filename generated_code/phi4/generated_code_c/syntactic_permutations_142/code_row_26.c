#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "your_database_name"

void unsubscribe(const char *email) {
    MYSQL conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Initialize connection
    if (mysql_init(&conn) == NULL) {
        fprintf(stderr, "MySQL initialization failed\n");
        exit(EXIT_FAILURE);
    }

    // Connect to the database
    if (!mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "Connection Error: %s\n", mysql_error(&conn));
        mysql_close(&conn);
        exit(EXIT_FAILURE);
    }

    // Prepare and execute the query
    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM subscribers WHERE email = '%s'", email);

    if (mysql_query(&conn, query)) {
        fprintf(stderr, "Query Execution Error: %s\n", mysql_error(&conn));
        mysql_close(&conn);
        exit(EXIT_FAILURE);
    }

    res = mysql_use_result(&conn);

    if ((row = mysql_fetch_row(res))) {
        int count = atoi(row[0]);
        if (count > 0) {
            printf("You have been successfully unsubscribed.\n");
        } else {
            printf("Email address not found in the database.\n");
        }
    }

    // Cleanup
    mysql_free_result(res);
    mysql_close(&conn);
}

int main() {
    char email[256];

    printf("Enter your email to unsubscribe: ");
    if (fgets(email, sizeof(email), stdin) != NULL) {
        // Remove newline character from input
        size_t len = strlen(email);
        if (len > 0 && email[len - 1] == '\n') {
            email[--len] = '\0';
        }

        unsubscribe(email);
    } else {
        fprintf(stderr, "Failed to read the email.\n");
    }

    return 0;
}