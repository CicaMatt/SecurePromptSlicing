#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *host = getenv("DB_HOST");
    const char *user = getenv("DB_USER");
    const char *password = getenv("DB_PASSWORD");
    const char *database = getenv("DB_NAME");
    const char *username_to_check = "example_user"; // Replace with the user you want to check

    if (!host || !user || !password || !database) {
        fprintf(stderr, "Database environment variables are not set.\n");
        return 1;
    }

    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return 1;
    }

    if (mysql_real_connect(conn, host, user, password, database, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE username = '%s'", username_to_check);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    res = mysql_store_result(conn);

    if (res == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    int is_moderator = 0;

    while ((row = mysql_fetch_row(res)) != NULL) {
        if (row[0] && strcmp(row[0], "true") == 0 || strcmp(row[0], "1") == 0) {
            is_moderator = 1;
        }
    }

    printf("%d\n", is_moderator);

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}