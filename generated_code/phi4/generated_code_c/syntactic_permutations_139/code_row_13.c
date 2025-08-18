#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *host = getenv("DB_HOST");
    const char *user = getenv("DB_USER");
    const char *password = getenv("DB_PASSWORD");
    const char *database = getenv("DB_NAME");

    if (!host || !user || !password || !database) {
        fprintf(stderr, "Database environment variables are not set.\n");
        return 1;
    }

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, host, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    const char *query = "SELECT is_moderator FROM users WHERE username='example_user'";

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    res = mysql_use_result(conn);

    int is_moderator = 0;

    while ((row = mysql_fetch_row(res))) {
        if (row[0] && strcmp(row[0], "true") == 0) {
            is_moderator = 1;
        }
    }

    printf("Is Moderator: %s\n", is_moderator ? "True" : "False");

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}


This code uses the MySQL C API to connect to a database and check if a user with username 'example_user' is a moderator. Ensure you have the MySQL client library installed and linked during compilation. You can compile it using:


gcc -o check_moderator your_file.c $(mysql_config --cflags --libs)


Replace `your_file.c` with the actual filename of your source code.