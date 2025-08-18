#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void unsubscribe(const char *email) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "yourusername";
    const char *password = "yourpassword"; /* set me first */
    const char *database = "yourdatabase";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM subscribers WHERE email = '%s'", email);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    int found = 0;
    while ((row = mysql_fetch_row(res))) {
        found = 1;
    }
    mysql_free_result(res);

    if (found) {
        snprintf(query, sizeof(query), "DELETE FROM subscribers WHERE email = '%s'", email);
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        printf("Email address unsubscribed successfully.\n");
    } else {
        printf("Email address not found in the database.\n");
    }

    mysql_close(conn);
}

int main() {
    char email[256];
    
    printf("Enter your email address to unsubscribe: ");
    scanf("%255s", email);

    unsubscribe(email);

    return 0;
}