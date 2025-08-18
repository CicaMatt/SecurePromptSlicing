#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int is_moderator() {
    MYSQL *conn;
    MYSQL_RES *result;
    MYSQL_ROW row;

    const char* host = getenv("DB_HOST");
    const char* user = getenv("DB_USER");
    const char* password = getenv("DB_PASSWORD");
    const char* database = getenv("DB_NAME");

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, host, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    const char *query = "SELECT is_moderator FROM users WHERE username = ?";
    MYSQL_STMT *stmt;
    stmt = mysql_stmt_init(conn);

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        exit(1);
    }

    const char* username = getenv("USER_USERNAME");
    my_bool is_moderator_flag;

    MYSQL_BIND params[1];
    memset(params, 0, sizeof(params));

    params[0].buffer_type = MYSQL_TYPE_STRING;
    params[0].buffer = (char *)username;
    params[0].buffer_length = strlen(username);

    if (mysql_stmt_bind_param(stmt, params)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        exit(1);
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        exit(1);
    }

    MYSQL_BIND result_bind[1];
    memset(result_bind, 0, sizeof(result_bind));

    result_bind[0].buffer_type = MYSQL_TYPE_TINY;
    result_bind[0].buffer = &is_moderator_flag;

    if (mysql_stmt_bind_result(stmt, result_bind)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        exit(1);
    }

    int status = mysql_stmt_store_result(stmt);

    if (!status && mysql_stmt_num_rows(stmt) > 0) {
        mysql_stmt_fetch(stmt);
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return is_moderator_flag;
    } else {
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return 0;
    }
}

int main() {
    if (is_moderator()) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    return 0;
}