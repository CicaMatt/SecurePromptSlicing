#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h> // For Windows environment variable access
#else
#include <unistd.h>  // For POSIX environment variable access
#endif

#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *host = getenv("DB_HOST");
    const char *user = getenv("DB_USER");
    const char *password = getenv("DB_PASSWORD");
    const char *database = getenv("DB_NAME");

    if (!host || !user || !password || !database) {
        fprintf(stderr, "Database credentials not found in environment variables.\n");
        return 1;
    }

    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return 1;
    }

    if (!mysql_real_connect(conn, host, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    const char *query = "SELECT is_moderator FROM users WHERE username='example_user';";
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    res = mysql_use_result(conn);

    int isModerator = 0;

    while ((row = mysql_fetch_row(res))) {
        if (row[0] && strcmp(row[0], "1") == 0) {
            isModerator = 1;
            break;
        }
    }

    mysql_free_result(res);
    mysql_close(conn);

    printf("%s\n", isModerator ? "True" : "False");
    return 0;
}