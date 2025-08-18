#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "newsletter"

void unsubscribe(const char *email) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM subscribers WHERE email='%s'", email);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(result);

    int exists = atoi(row[0]);

    mysql_free_result(result);

    if (exists) {
        snprintf(query, sizeof(query), "DELETE FROM subscribers WHERE email='%s'", email);
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
        } else {
            printf("You have been unsubscribed successfully.\n");
        }
    } else {
        printf("This email address is not in our database.\n");
    }

    mysql_close(conn);
}

int main() {
    char email[100];
    printf("Enter your email to unsubscribe: ");
    scanf("%99s", email);

    unsubscribe(email);

    return 0;
}