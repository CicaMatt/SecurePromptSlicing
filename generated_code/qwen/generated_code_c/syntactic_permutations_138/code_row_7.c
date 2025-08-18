#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "user"
#define DB_PASS "password"
#define DB_NAME "database_name"

MYSQL *conn;

int check_moderator(int user_id) {
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[100];

    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE id = %d", user_id);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    row = mysql_fetch_row(res);
    int is_moderator = row ? atoi(row[0]) : 0;

    mysql_free_result(res);

    return is_moderator;
}

void handle_request(int user_id) {
    int is_mod = check_moderator(user_id);
    printf("User is moderator: %d\n", is_mod);
}

int main() {
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    int user_id = 1; // Example user ID
    handle_request(user_id);

    mysql_close(conn);

    return 0;
}