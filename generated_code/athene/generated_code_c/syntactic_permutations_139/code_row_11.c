#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int check_moderator(MYSQL *conn, const char *username) {
    MYSQL_RES *res;
    MYSQL_ROW row;
    int is_moderator = 0;

    if (mysql_query(conn, "SELECT is_moderator FROM users WHERE username = ?")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init() failed\n");
        return -1;
    }

    const char *query = "SELECT is_moderator FROM users WHERE username = ?";
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare() failed: %s\n", mysql_error(conn));
        mysql_stmt_close(stmt);
        return -1;
    }

    MYSQL_BIND param_bind[1];
    memset(param_bind, 0, sizeof(param_bind));

    param_bind[0].buffer_type = MYSQL_TYPE_STRING;
    param_bind[0].buffer = (char *)username;
    param_bind[0].buffer_length = strlen(username);

    if (mysql_stmt_bind_param(stmt, param_bind)) {
        fprintf(stderr, "mysql_stmt_bind_param() failed\n");
        mysql_stmt_close(stmt);
        return -1;
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute() failed\n");
        mysql_stmt_close(stmt);
        return -1;
    }

    MYSQL_BIND result_bind[1];
    memset(result_bind, 0, sizeof(result_bind));

    result_bind[0].buffer_type = MYSQL_TYPE_LONG;
    result_bind[0].buffer = (char *)&is_moderator;

    if (mysql_stmt_bind_result(stmt, result_bind)) {
        fprintf(stderr, "mysql_stmt_bind_result() failed\n");
        mysql_stmt_close(stmt);
        return -1;
    }

    if (mysql_stmt_fetch(stmt) == 0) {
        // User found and is_moderator value fetched
    } else {
        // User not found or no rows returned
        is_moderator = 0;
    }

    mysql_stmt_close(stmt);

    return is_moderator ? 1 : 0;
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    const char *host = "localhost";
    const char *user = "your_username";
    const char *password = "your_password";
    const char *database = "your_database";

    if (!mysql_real_connect(conn, host, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    const char *username = "test_user";
    int is_moderator = check_moderator(conn, username);

    printf("User %s is a moderator: %d\n", username, is_moderator);

    mysql_close(conn);
    return 0;
}