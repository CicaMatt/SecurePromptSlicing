#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mysql/mysql.h"

int main() {
    char *db_host = getenv("DB_HOST");
    char *db_user = getenv("DB_USER");
    char *db_password = getenv("DB_PASSWORD");
    char *db_name = getenv("DB_NAME");

    int db_port = 3006;

    // Initialize client and test connection
    MYSQL mysql;
    mysql_init(&mysql);

    if (!mysql_real_connect(
            &mysql,
            db_host, db_user, db_password,
            db_name,
            db_port, NULL, 0)) {
        printf("Failed to connect to database\n");
        return 1;
    }

    // Prepare query statement
    char *query = "SELECT EXISTS(SELECT 1 FROM users WHERE username=?);";
    MYSQL_STMT *stmt = mysql_stmt_init(&mysql);
    mysql_stmt_prepare(stmt, query, strlen(query));

    // Bind input parameter
    char username[64];
    strcpy(username, "testuser");
    MYSQL_BIND input_bind[1];
    memset(input_bind, 0, sizeof(input_bind));

    input_bind[0].buffer_type = MYSQL_TYPE_STRING;
    input_bind[0].buffer = username;
    input_bind[0].buffer_length = strlen(username);

    mysql_stmt_bind_param(stmt, input_bind);

    // Execute query
    int result = mysql_stmt_execute(stmt);
    if (result != 0) {
        printf("Failed to execute statement\n");
        return 1;
    }

    // Get the result of EXISTS()
    MYSQL_BIND output_bind[1];
    memset(output_bind, 0, sizeof(output_bind));

    output_bind[0].buffer_type = MYSQL_TYPE_LONG;
    unsigned long user_exists = 0;
    output_bind[0].buffer = &user_exists;
    output_bind[0].is_null = 0;
    output_bind[0].length = NULL;

    mysql_stmt_bind_result(stmt, output_bind);
    mysql_stmt_store_result(stmt);

    while (mysql_stmt_fetch(stmt) != MYSQL_NO_DATA) {
        if (user_exists > 0) {
            printf("User exists!\n");
            return 1;
        }
    }

    // Cleanup
    mysql_stmt_close(stmt);
    mysql_close(&mysql);

    return 0;
}