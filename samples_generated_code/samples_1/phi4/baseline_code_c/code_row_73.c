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

    if (!host || !user || !password || !database) {
        fprintf(stderr, "Database credentials are not set in environment variables.\n");
        return 1;
    }

    conn = mysql_init(NULL);

    if (mysql_real_connect(conn, host, user, password, database, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    const char *query = "SELECT is_moderator FROM users WHERE username = 'example_user'";
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

    mysql_free_result(res);
    mysql_close(conn);

    printf("%d\n", isModerator);

    return 0;
}


To compile and run this code, you need to have MySQL client library installed. You can compile it using:


gcc -o check_moderator check_moderator.c $(mysql_config --cflags --libs)


Make sure the environment variables `DB_HOST`, `DB_USER`, `DB_PASSWORD`, and `DB_NAME` are set before running the program. Adjust the query as necessary to fit your actual database schema.