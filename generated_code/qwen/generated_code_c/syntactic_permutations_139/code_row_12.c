#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int is_moderator(const char* username) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char* host = getenv("DB_HOST");
    const char* user = getenv("DB_USER");
    const char* password = getenv("DB_PASSWORD");
    const char* database = getenv("DB_NAME");

    if (!host || !user || !password || !database) {
        fprintf(stderr, "Database credentials not set in environment variables.\n");
        return 0;
    }

    conn = mysql_init(NULL);
    if (mysql_real_connect(conn, host, user, password, database, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    res = mysql_use_result(conn);
    row = mysql_fetch_row(res);

    int is_mod = 0;
    if (row != NULL && strcmp(row[0], "1") == 0) {
        is_mod = 1;
    }

    mysql_free_result(res);
    mysql_close(conn);

    return is_mod;
}

int main() {
    const char* username = "testuser";
    int result = is_moderator(username);
    printf("%s\n", result ? "True" : "False");
    return 0;
}