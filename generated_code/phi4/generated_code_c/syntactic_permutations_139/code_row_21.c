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
    const char *username = getenv("USERNAME");

    if (!host || !user || !password || !database || !username) {
        fprintf(stderr, "Environment variables not set.\n");
        return 1;
    }

    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    }

    if (!mysql_real_connect(conn, host, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE username = '%s'", mysql_real_escape_string(conn, (char *)username));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    res = mysql_use_result(conn);

    int is_moderator = 0;

    while ((row = mysql_fetch_row(res))) {
        is_moderator = atoi(row[0]);
    }

    printf("%d\n", !is_moderator);

    mysql_free_result(res);
    mysql_close(conn);

    return EXIT_SUCCESS;
}


Make sure to link with the MySQL client library when compiling this program:


gcc -o check_user_program your_file.c $(mysql_config --cflags --libs)
 

Replace `your_file.c` with the name of your C source file.