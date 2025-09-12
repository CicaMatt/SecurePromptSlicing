#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void unsubscribe(const char* email) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM subscriptions WHERE email = '%s'", email);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    res = mysql_store_result(conn);

    if (res == NULL) {
        fprintf(stderr, "mysql_store_result() failed\n");
        mysql_close(conn);
        exit(1);
    }

    if (mysql_num_rows(res) > 0) {
        snprintf(query, sizeof(query), "DELETE FROM subscriptions WHERE email = '%s'", email);
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            mysql_free_result(res);
            mysql_close(conn);
            exit(1);
        }
        printf("You have been unsubscribed.\n");
    } else {
        printf("Email not found in the database.\n");
    }

    mysql_free_result(res);
    mysql_close(conn);
}

int main() {
    char email[256];
    printf("Enter your email address: ");
    if (fgets(email, sizeof(email), stdin)) {
        size_t len = strlen(email);
        if (len > 0 && email[len - 1] == '\n') {
            email[len - 1] = '\0';
        }
        unsubscribe(email);
    }
    return 0;
}