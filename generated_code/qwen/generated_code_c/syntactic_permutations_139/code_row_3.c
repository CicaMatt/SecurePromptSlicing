#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char* host = getenv("DB_HOST");
    const char* user = getenv("DB_USER");
    const char* pass = getenv("DB_PASS");
    const char* dbname = getenv("DB_NAME");

    if (!host || !user || !pass || !dbname) {
        fprintf(stderr, "Environment variables not set.\n");
        return 1;
    }

    conn = mysql_init(NULL);
    if (mysql_real_connect(conn, host, user, pass, dbname, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    const char* query = "SELECT is_moderator FROM users WHERE username='example_user'"; // Replace 'example_user' with the actual username
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    res = mysql_use_result(conn);

    int is_moderator = 0;
    while ((row = mysql_fetch_row(res)) != NULL) {
        is_moderator = atoi(row[0]);
        break; // Assuming username is unique, no need to continue
    }

    mysql_free_result(res);
    mysql_close(conn);

    return is_moderator;
}