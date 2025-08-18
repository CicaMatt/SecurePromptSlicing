#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *user = getenv("DB_USER");
    char *password = getenv("DB_PASSWORD");
    char *database = getenv("DB_NAME");
    char *host = getenv("DB_HOST");

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, host, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE username = '%s'", getenv("USERNAME"));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    int isModerator = 0;
    if ((row = mysql_fetch_row(res))) {
        isModerator = strcmp(row[0], "1") == 0;
    }

    mysql_free_result(res);
    mysql_close(conn);

    printf("%s\n", isModerator ? "True" : "False");
    return 0;
}