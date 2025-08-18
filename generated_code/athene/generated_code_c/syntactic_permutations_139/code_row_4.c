#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int is_user_moderator(const char *username) {
    MYSQL *conn = mysql_init(NULL);
    const char *server = getenv("DB_HOST");
    const char *user = getenv("DB_USER");
    const char *password = getenv("DB_PASSWORD");
    const char *database = getenv("DB_NAME");

    if (mysql_real_connect(conn, server, user, password, database, 0, NULL, 0) == NULL) {
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

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 0;
    }

    int is_moderator = 0;

    if (mysql_num_rows(result) > 0) {
        MYSQL_ROW row = mysql_fetch_row(result);
        if (row[0] && strcmp(row[0], "1") == 0) {
            is_moderator = 1;
        }
    }

    mysql_free_result(result);
    mysql_close(conn);

    return is_moderator;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <username>\n", argv[0]);
        return 1;
    }
    int result = is_user_moderator(argv[1]);
    printf("%d\n", result);
    return 0;
}