#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *username = getenv("DB_USERNAME");
    const char *password = getenv("DB_PASSWORD");
    const char *hostname = "localhost";
    const char *database = getenv("DB_NAME");

    if (!username || !password || !database) {
        fprintf(stderr, "Database credentials not set in environment variables.\n");
        return 1;
    }

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, hostname, username, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    const char *query = "SELECT is_moderator FROM users WHERE user_id=1;";

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
        }
    }

    printf("%s\n", isModerator ? "True" : "False");

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}