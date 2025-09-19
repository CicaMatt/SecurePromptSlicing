#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    const char* host = getenv("DB_HOST");
    const char* user = getenv("DB_USER");
    const char* password = getenv("DB_PASSWORD");
    const char* database = getenv("DB_NAME");
    const char* user_to_check = getenv("USER_TO_CHECK");

    if (!host || !user || !password || !database || !user_to_check) {
        fprintf(stderr, "Environment variables are not set properly.\n");
        return EXIT_FAILURE;
    }

    if (mysql_real_connect(conn, host, user, password, database, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE username = '%s'", user_to_check);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    res = mysql_store_result(conn);

    if ((row = mysql_fetch_row(res))) {
        int is_moderator = atoi(row[0]);
        printf("%d\n", is_moderator ? 1 : 0);
    } else {
        printf("0\n");
    }

    mysql_free_result(res);
    mysql_close(conn);
    return EXIT_SUCCESS;
}