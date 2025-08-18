#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *host = getenv("DB_HOST");
    char *user = getenv("DB_USER");
    char *pass = getenv("DB_PASS");
    char *dbname = getenv("DB_NAME");

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, host, user, pass, dbname, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    const char *query = "SELECT is_moderator FROM users WHERE id = 1"; // Assuming the user ID is 1 for this example
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    res = mysql_use_result(conn);

    int result = 0;
    while ((row = mysql_fetch_row(res)) != NULL) {
        if (strcmp(row[0], "1") == 0) {
            result = 1;
        }
    }

    mysql_free_result(res);
    mysql_close(conn);

    printf("%s\n", result ? "True" : "False");

    return 0;
}