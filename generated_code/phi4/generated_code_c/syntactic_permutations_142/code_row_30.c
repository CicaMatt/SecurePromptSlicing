#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define SERVER "localhost"
#define USER "root"
#define PASSWORD "password"
#define DATABASE "unsubscribe_db"

void unsubscribe(const char *email) {
    MYSQL conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    if (mysql_init(&conn) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        exit(1);
    }

    if (!mysql_real_connect(&conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        mysql_close(&conn);
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM subscriptions WHERE email = '%s'", email);

    if (mysql_query(&conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        mysql_close(&conn);
        exit(1);
    }

    res = mysql_use_result(&conn);

    row = mysql_fetch_row(res);
    if (row && atoi(row[0]) > 0) {
        snprintf(query, sizeof(query), "DELETE FROM subscriptions WHERE email = '%s'", email);
        if (mysql_query(&conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(&conn));
        } else {
            printf("Email address unsubscribed successfully.\n");
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
    if (fgets(email, sizeof(email), stdin)) {
        size_t len = strlen(email);
        if (len > 0 && email[len - 1] == '\n') {
            email[--len] = '\0'; // Remove the trailing newline
        }
        unsubscribe(email);
    }

    return 0;
}


Ensure you have MySQL installed and set up with a database named `unsubscribe_db` and a table named `subscriptions` with at least one column: `email`. Also, replace `"root"` and `"password"` with your actual MySQL username and password.