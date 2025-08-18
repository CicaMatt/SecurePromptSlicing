#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    int is_moderator = 0;

    const char* host = getenv("DB_HOST");
    const char* user = getenv("DB_USER");
    const char* password = getenv("DB_PASSWORD");
    const char* database = getenv("DB_NAME");

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, host, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    const char* query = "SELECT is_moderator FROM users WHERE username = ?";
    MYSQL_STMT *stmt;
    stmt = mysql_stmt_init(conn);

    if (!mysql_stmt_prepare(stmt, query, strlen(query))) {
        MYSQL_BIND bind[1];
        memset(bind, 0, sizeof(bind));

        const char* username = getenv("USERNAME");
        unsigned long username_length = strlen(username);

        bind[0].buffer_type = MYSQL_TYPE_STRING;
        bind[0].buffer = (char *)username;
        bind[0].buffer_length = username_length;

        if (!mysql_stmt_bind_param(stmt, bind)) {
            mysql_stmt_execute(stmt);
            res = mysql_stmt_result_metadata(stmt);

            if (res) {
                int num_fields = mysql_num_fields(res);
                MYSQL_BIND result[1];
                memset(result, 0, sizeof(result));

                my_bool is_null[1];
                my_bool error[1];

                result[0].buffer_type = MYSQL_TYPE_LONG;
                result[0].is_null = &is_null[0];
                result[0].error = &error[0];

                if (!mysql_stmt_bind_result(stmt, result)) {
                    while (!mysql_stmt_fetch(stmt)) {
                        is_moderator = *(int *)result[0].buffer;
                    }
                }

                mysql_free_result(res);
            }
        }
    } else {
        fprintf(stderr, "Could not prepare statement: %s\n", mysql_error(conn));
    }

    mysql_stmt_close(stmt);
    mysql_close(conn);

    printf("%s\n", is_moderator ? "True" : "False");
    return 0;
}