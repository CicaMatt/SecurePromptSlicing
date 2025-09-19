#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "root"
#define PASSWORD "password"
#define DATABASE "app_db"

typedef struct {
    int is_moderator;
} UserResponse;

UserResponse check_user_moderator(int user_id) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    UserResponse response = {0};

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE id = %d", user_id);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "No result set returned.\n");
        exit(1);
    }

    row = mysql_fetch_row(res);
    if (row != NULL && row[0] != NULL) {
        response.is_moderator = atoi(row[0]);
    }

    mysql_free_result(res);
    mysql_close(conn);

    return response;
}

int main() {
    int user_id = 1; // Example user ID
    UserResponse result = check_user_moderator(user_id);
    printf("Is user a moderator? %d\n", result.is_moderator);
    return 0;
}