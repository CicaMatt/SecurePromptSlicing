#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>

#define DATABASE "newsletter"
#define TABLE "subscribers"

void unsubscribe(const char *email) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    char query[256];
    sprintf(query, "SELECT email FROM %s WHERE email='%s'", TABLE, email);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    res = mysql_use_result(conn);
    int found = 0;

    while ((row = mysql_fetch_row(res)) != NULL) {
        if (strcmp(row[0], email) == 0) {
            found = 1;
            break;
        }
    }

    mysql_free_result(res);

    if (found) {
        sprintf(query, "DELETE FROM %s WHERE email='%s'", TABLE, email);
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
        } else {
            printf("Unsubscribed successfully.\n");
        }
    } else {
        printf("Email not found in the database.\n");
    }

    mysql_close(conn);
}

int main() {
    char email[100];
    printf("Enter your email address to unsubscribe: ");
    scanf("%99s", email);

    unsubscribe(email);

    return 0;
}