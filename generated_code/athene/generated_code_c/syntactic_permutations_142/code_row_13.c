#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>

#define MYSQL_USER "your_username"
#define MYSQL_PASSWORD "your_password"
#define MYSQL_DATABASE "your_database"
#define MYSQL_HOST "localhost"

void check_unsubscribe(const char *email) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    char query[256];
    snprintf(query, sizeof(query), "DELETE FROM subscribers WHERE email = '%s'", mysql_real_escape_string(conn, (char *)email, strlen(email)));

    if (mysql_query(conn, query) == 0) {
        MYSQL_RES *result = mysql_store_result(conn);
        if (mysql_affected_rows(conn) > 0) {
            printf("You have been successfully unsubscribed.\n");
        } else {
            printf("Email address not found in the database. You are already unsubscribed.\n");
        }
        if (result) mysql_free_result(result);
    } else {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }

    mysql_close(conn);
}

int main() {
    char email[100];
    printf("Enter your email address to unsubscribe: ");
    scanf("%99s", email);

    check_unsubscribe(email);

    return 0;
}