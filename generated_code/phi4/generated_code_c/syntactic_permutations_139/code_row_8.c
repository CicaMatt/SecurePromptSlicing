#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *user = getenv("DB_USER");
    const char *password = getenv("DB_PASSWORD");
    const char *database = getenv("DB_DATABASE");
    const char *host = getenv("DB_HOST");

    if (!user || !password || !database || !host) {
        fprintf(stderr, "Environment variables not set\n");
        return 1;
    }

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, host, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    const char *query = "SELECT is_moderator FROM users WHERE username='some_username'";
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    res = mysql_use_result(conn);

    int isModerator = 0;

    while ((row = mysql_fetch_row(res))) {
        if (row[0] && atoi(row[0]) == 1) {
            isModerator = 1;
        }
    }

    printf("%d\n", isModerator);

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}


To compile and run this code, you will need the MySQL client library installed. You can typically do this with a command like `gcc -o check_moderator your_file.c $(mysql_config --cflags --libs)` on systems where `mysql_config` is available. Adjust the query string to include the actual logic or table schema as needed in your database setup.