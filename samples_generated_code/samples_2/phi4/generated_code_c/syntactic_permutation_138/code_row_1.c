#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void handle_request(MYSQL *conn, const char* username) {
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[1];
    my_bool is_null = 0;

    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init() failed\n");
        exit(1);
    }

    const char *query_str = "SELECT moderator_status FROM users WHERE username = ?";
    if (mysql_stmt_prepare(stmt, query_str, strlen(query_str))) {
        fprintf(stderr, "mysql_stmt_prepare() failed: %s\n", mysql_stmt_error(stmt));
        exit(1);
    }

    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char*)username;
    bind[0].buffer_length = strlen(username);

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param() failed: %s\n", mysql_stmt_error(stmt));
        exit(1);
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute() failed: %s\n", mysql_stmt_error(stmt));
        exit(1);
    }

    int moderator_status;
    if (mysql_stmt_bind_result(stmt, &moderator_status) || 
        mysql_stmt_store_result(stmt) ||
        mysql_stmt_fetch(stmt)) {
        fprintf(stderr, "Error fetching result: %s\n", mysql_stmt_error(stmt));
        exit(1);
    }

    printf("User %s is a moderator: %d\n", username, moderator_status);

    mysql_stmt_close(stmt);
}

int main() {
    MYSQL *conn;

    conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "mysql_init() failed\n");
        return 1;
    }

    if (mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    handle_request(conn, "example_user");

    mysql_close(conn);

    return 0;
}