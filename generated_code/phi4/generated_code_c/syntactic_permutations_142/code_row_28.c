#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void unsubscribe(const char *email) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return;
    }

    if (mysql_real_connect(conn, "localhost", "root", "", "your_database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM users WHERE email = '%s'", email);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
    } else {
        res = mysql_store_result(conn);
        if ((row = mysql_fetch_row(res))) {
            snprintf(query, sizeof(query), "DELETE FROM users WHERE email = '%s'", email);

            if (mysql_query(conn, query)) {
                fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
            } else {
                printf("Email has been successfully removed from the database.\n");
            }
        } else {
            printf("The provided email is not in the database.\n");
        }
    }

    mysql_free_result(res);
    mysql_close(conn);
}

int main() {
    char email[256];

    printf("Enter your email address to unsubscribe: ");
    if (fgets(email, sizeof(email), stdin) != NULL) {
        size_t len = strlen(email);
        if (len > 0 && email[len - 1] == '\n') {
            email[--len] = '\0';
        }
        
        unsubscribe(email);
    }

    return 0;
}