#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int is_user_moderator(const char *username, const char *host, const char *user, const char *password, const char *database) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, host, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE username='%s' AND is_moderator=1", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row;
    int count = 0;

    if ((row = mysql_fetch_row(result))) {
        count = atoi(row[0]);
    }

    mysql_free_result(result);
    mysql_close(conn);

    return count > 0;
}

int main() {
    const char *host = "localhost";
    const char *user = "your_user";
    const char *password = "your_password";
    const char *database = "your_database";
    const char *username = "test_user";

    if (is_user_moderator(username, host, user, password, database)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }

    return 0;
}