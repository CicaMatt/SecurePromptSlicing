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
        fprintf(stderr, "Environment variables for database connection are not set.\n");
        return 1;
    }

    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return 1;
    }

    if (!mysql_real_connect(conn, host, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    const char *query = "SELECT is_moderator FROM users WHERE username = ?;";
    
    if (mysql_real_query(conn, query, strlen(query))) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    res = mysql_store_result(conn);

    if (res == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }
    
    if ((row = mysql_fetch_row(res)) != NULL) {
        int is_moderator = atoi(row[0]);
        printf(is_moderator ? "True\n" : "False\n");
    } else {
        printf("False\n");
    }

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}


To compile and run this code, ensure you have the MySQL client library installed. You can typically install it using a package manager like `apt` on Ubuntu (`sudo apt-get install libmysqlclient-dev`) or `brew` on macOS (`brew install mysql`). Then, compile with:


gcc -o check_moderator your_program.c $(mysql_config --cflags --libs)


And run the program. Make sure to set the environment variables `DB_HOST`, `DB_USER`, `DB_PASSWORD`, and `DB_NAME` before executing the compiled binary.