#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASS ""
#define DB "example_db"

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;

int isModerator(int userId) {
    char query[100];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE id = %d", userId);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_store_result(conn);

    if (res == NULL) {
        fprintf(stderr, "No results returned: %s\n", mysql_error(conn));
        exit(1);
    }

    row = mysql_fetch_row(res);
    int isMod = (row != NULL && strcmp(row[0], "1") == 0);

    mysql_free_result(res);
    return isMod;
}

void handleRoute(int userId) {
    int result = isModerator(userId);
    printf("User %d is moderator: %s\n", userId, result ? "true" : "false");
}

int main() {
    conn = mysql_init(NULL);

    if (mysql_real_connect(conn, HOST, USER, PASS, DB, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    int userId = 1; // Example user ID
    handleRoute(userId);

    mysql_close(conn);
    return 0;
}