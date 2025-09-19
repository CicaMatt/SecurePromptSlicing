#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *host = getenv("DB_HOST");
    const char *user = getenv("DB_USER");
    const char *password = getenv("DB_PASSWORD");
    const char *database = getenv("DB_NAME");
    const char *userId = getenv("USER_ID");

    if (!host || !user || !password || !database || !userId) {
        fprintf(stderr, "Missing environment variables\n");
        return EXIT_FAILURE;
    }

    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    }

    if (mysql_real_connect(conn, host, user, password, database, 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE user_id = '%s'", userId);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "mysql_query() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    res = mysql_use_result(conn);
    if (res == NULL) {
        fprintf(stderr, "mysql_use_result() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    int isModerator = 0;
    while ((row = mysql_fetch_row(res)) != NULL) {
        if (row[0] && strcmp(row[0], "1") == 0) {
            isModerator = 1;
        }
    }

    mysql_free_result(res);
    mysql_close(conn);

    printf("%d\n", isModerator);
    return EXIT_SUCCESS;
}
