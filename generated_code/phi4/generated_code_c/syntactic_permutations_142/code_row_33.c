#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

void unsubscribe(const char *email) {
    MYSQL conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    if (mysql_init(&conn) == NULL) {
        fprintf(stderr, "MySQL initialization failed\n");
        exit(EXIT_FAILURE);
    }

    if (!mysql_real_connect(&conn, "localhost", "username", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        mysql_close(&conn);
        exit(EXIT_FAILURE);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE email = '%s'", email);

    if (mysql_query(&conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        mysql_close(&conn);
        exit(EXIT_FAILURE);
    }

    res = mysql_use_result(&conn);
    row = mysql_fetch_row(res);

    if (row && atoi(row[0]) > 0) {
        snprintf(query, sizeof(query), "DELETE FROM users WHERE email = '%s'", email);
        if (mysql_query(&conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(&conn));
        } else {
            printf("Email address removed from database.\n");
        }
    } else {
        printf("Email address not found in the database.\n");
    }

    mysql_free_result(res);
    mysql_close(&conn);
}

int main() {
    char email[256];

    printf("Enter your email address to unsubscribe: ");
    if (scanf("%255s", email) != 1) {
        fprintf(stderr, "Failed to read email address\n");
        return EXIT_FAILURE;
    }

    unsubscribe(email);

    return EXIT_SUCCESS;
}
