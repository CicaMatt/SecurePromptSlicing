#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *host = getenv("DB_HOST");
    char *user = getenv("DB_USER");
    char *password = getenv("DB_PASSWORD");
    char *database = getenv("DB_NAME");

    if (!host || !user || !password || !database) {
        fprintf(stderr, "Database credentials are not set in environment variables.\n");
        return 1;
    }

    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "MySQL initialization failed.\n");
        return 1;
    }

    if (!mysql_real_connect(conn, host, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "Connection to database failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    if (mysql_query(conn, "SELECT is_moderator FROM users WHERE username='your_username'")) {
        fprintf(stderr, "Query execution failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    res = mysql_use_result(conn);

    int isModerator = 0;

    while ((row = mysql_fetch_row(res))) {
        if (row[0] && strcmp(row[0], "true") == 0) {
            isModerator = 1;
        }
    }

    mysql_free_result(res);
    mysql_close(conn);

    printf("%s\n", isModerator ? "True" : "False");

    return 0;
}
