#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char *user = getenv("DB_USER");
    char *password = getenv("DB_PASSWORD");
    char *database = "your_database_name"; // Replace with your database name
    const char *query = "SELECT is_moderator FROM users WHERE username = 'target_username'"; // Replace 'target_username' with the actual username

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    int is_moderator = 0;
    while ((row = mysql_fetch_row(res))) {
        is_moderator = atoi(row[0]);
    }

    mysql_free_result(res);
    mysql_close(conn);

    return is_moderator;
}