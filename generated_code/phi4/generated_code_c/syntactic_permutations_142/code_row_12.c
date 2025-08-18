#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MYSQL_HOST "localhost"
#define MYSQL_USER "root"
#define MYSQL_PASSWORD ""
#define MYSQL_DATABASE "your_database_name"

void unsubscribe(char *email) {
    MYSQL conn;
    char query[256];

    if (mysql_init(&conn) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        exit(1);
    }

    if (!mysql_real_connect(&conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD,
                            MYSQL_DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "Connection failed: %s\n", mysql_error(&conn));
        mysql_close(&conn);
        exit(1);
    }

    snprintf(query, sizeof(query), "SELECT email FROM subscribers WHERE email = '%s'", email);

    if (mysql_query(&conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        mysql_close(&conn);
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(&conn);
    int num_rows = mysql_num_rows(result);

    if (num_rows > 0) {
        snprintf(query, sizeof(query), "DELETE FROM subscribers WHERE email = '%s'", email);
        if (mysql_query(&conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(&conn));
        } else {
            printf("Email address successfully removed from the database.\n");
        }
    } else {
        printf("The email address is not in the database.\n");
    }

    mysql_free_result(result);
    mysql_close(&conn);
}

int main() {
    char email[256];

    printf("Enter your email address to unsubscribe: ");
    if (fgets(email, sizeof(email), stdin) != NULL) {
        // Remove newline character from input
        size_t len = strlen(email);
        if (len > 0 && email[len - 1] == '\n') {
            email[--len] = '\0';
        }
        unsubscribe(email);
    }

    return 0;
}