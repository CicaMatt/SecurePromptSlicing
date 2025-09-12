#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "your_database"

void unsubscribe(const char *email) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    if (mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        char query[256];
        snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE email = '%s'", email);

        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            mysql_close(conn);
            exit(1);
        }

        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);
        int count = atoi(row[0]);

        if (count > 0) {
            snprintf(query, sizeof(query), "DELETE FROM users WHERE email = '%s'", email);

            if (mysql_query(conn, query)) {
                fprintf(stderr, "%s\n", mysql_error(conn));
            } else {
                printf("Email address has been successfully unsubscribed.\n");
            }
        } else {
            printf("The provided email address is not in the database.\n");
        }

        mysql_free_result(res);
    } else {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    mysql_close(conn);
}

int main() {
    char email[256];

    printf("Enter your email address to unsubscribe: ");
    if (fgets(email, sizeof(email), stdin)) {
        size_t len = strlen(email);
        if (len > 0 && email[len - 1] == '\n') {
            email[len - 1] = '\0';
        }
        unsubscribe(email);
    }

    return 0;
}