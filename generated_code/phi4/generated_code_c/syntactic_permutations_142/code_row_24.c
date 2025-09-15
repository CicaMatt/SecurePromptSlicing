#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void unsubscribe(const char* email) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "root";
    const char *password = "";
    const char *database = "your_database_name";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM subscribers WHERE email = '%s'", email);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    res = mysql_use_result(conn);

    while ((row = mysql_fetch_row(res))) {
        int count = atoi(row[0]);
        if (count > 0) {
            snprintf(query, sizeof(query), "DELETE FROM subscribers WHERE email = '%s'", email);
            if (mysql_query(conn, query)) {
                fprintf(stderr, "%s\n", mysql_error(conn));
            } else {
                printf("Unsubscribed successfully.\n");
            }
        } else {
            printf("Email address not found in database.\n");
        }
    }

    mysql_free_result(res);
    mysql_close(conn);
}

int main() {
    char email[256];

    printf("Enter your email to unsubscribe: ");
    if (fgets(email, sizeof(email), stdin)) {
        size_t len = strlen(email);
        if (len > 0 && email[len - 1] == '\n') {
            email[--len] = '\0';
        }
        unsubscribe(email);
    }

    return 0;
}
