#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "password"
#define DB_NAME "database_name"

void unsubscribe(const char *email) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    const char *query_check = "SELECT COUNT(*) FROM users WHERE email = ?";
    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    if (mysql_stmt_prepare(stmt, query_check, strlen(query_check)) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        goto cleanup;
    }

    my_bool param_true = 1;
    mysql_stmt_bind_param(stmt, "s", &email);
    mysql_stmt_execute(stmt);
    MYSQL_BIND result_bind[1];
    unsigned long *count = (unsigned long *)malloc(sizeof(unsigned long));
    memset(result_bind, 0, sizeof(result_bind));
    result_bind[0].buffer_type = MYSQL_TYPE_LONG;
    result_bind[0].buffer = count;
    if (mysql_stmt_bind_result(stmt, result_bind) != 0 || mysql_stmt_fetch(stmt) != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        goto cleanup;
    }

    if (*count > 0) {
        const char *query_delete = "DELETE FROM users WHERE email = ?";
        MYSQL_STMT *stmt_del = mysql_stmt_init(conn);
        if (mysql_stmt_prepare(stmt_del, query_delete, strlen(query_delete)) != 0) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            goto cleanup;
        }
        mysql_stmt_bind_param(stmt_del, "s", &email);
        if (mysql_stmt_execute(stmt_del) != 0) {
            fprintf(stderr, "%s\n", mysql_error(conn));
        } else {
            printf("You have been successfully unsubscribed.\n");
        }
        mysql_stmt_close(stmt_del);
    } else {
        printf("Email address not found. You are already unsubscribed or never subscribed.\n");
    }

cleanup:
    free(count);
    mysql_stmt_close(stmt);
    mysql_close(conn);
}

int main() {
    char email[256];
    printf("Enter your email to unsubscribe: ");
    scanf("%255s", email);
    unsubscribe(email);
    return 0;
}