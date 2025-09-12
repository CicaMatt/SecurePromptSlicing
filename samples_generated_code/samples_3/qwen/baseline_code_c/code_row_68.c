#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "your_username"
#define DB_PASS "your_password"
#define DB_NAME "your_database"

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;

void checkModerator(int userId) {
    char query[100];
    sprintf(query, "SELECT is_moderator FROM users WHERE id = %d", userId);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res)) != NULL) {
        printf("Is moderator: %s\n", row[0]);
    } else {
        printf("User not found.\n");
    }

    mysql_free_result(res);
}

int main() {
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    int userId = 1; // Example user ID
    checkModerator(userId);

    mysql_close(conn);
    return 0;
}