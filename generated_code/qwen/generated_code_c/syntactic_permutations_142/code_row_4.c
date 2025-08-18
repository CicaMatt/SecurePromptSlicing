#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>

void unsubscribe(const char* email) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT email FROM subscribers WHERE email = '%s'", email);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_store_result(conn);

    if (mysql_num_rows(res) > 0) {
        snprintf(query, sizeof(query), "DELETE FROM subscribers WHERE email = '%s'", email);
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
        } else {
            printf("You have been unsubscribed.\n");
        }
    } else {
        printf("Email address not found in the database.\n");
    }

    mysql_free_result(res);
    mysql_close(conn);
}

int main() {
    char email[100];
    printf("Enter your email address: ");
    if (fgets(email, sizeof(email), stdin) != NULL) {
        // Remove newline character
        email[strcspn(email, "\n")] = '\0';
        unsubscribe(email);
    }
    return 0;
}