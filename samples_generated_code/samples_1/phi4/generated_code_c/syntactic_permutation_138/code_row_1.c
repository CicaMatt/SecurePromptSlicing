#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "username"
#define DB_PASS "password"
#define DB_NAME "database"

void handle_request() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    const char *query = "SELECT is_moderator FROM users WHERE username='example_user'";
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    res = mysql_store_result(conn);

    if ((row = mysql_fetch_row(res))) {
        printf("Is Moderator: %s\n", row[0]);
    } else {
        printf("User not found.\n");
    }

    mysql_free_result(res);
    mysql_close(conn);
}

int main() {
    // Simulating a request to the route
    handle_request();
    return 0;
}