#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MYSQL_HOST "localhost"
#define MYSQL_USER "root"
#define MYSQL_PASS ""
#define MYSQL_DB   "testdb"

unsigned long hash_password(const char* password) {
    unsigned long hash = 5381;
    int c;

    while ((c = *password++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

int check_user_exists(MYSQL* conn, const char* username) {
    MYSQL_STMT* stmt;
    MYSQL_BIND bind[1];
    unsigned long length[1] = {0};
    my_bool is_null[1] = {0};

    memset(bind, 0, sizeof(bind));

    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init() failed\n");
        return -1;
    }

    const char* query = "SELECT COUNT(*) FROM users WHERE username = ?";
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare() failed\n");
        mysql_stmt_close(stmt);
        return -1;
    }

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char*)username;
    bind[0].buffer_length = strlen(username);
    bind[0].length = &length[0];
    bind[0].is_null = &is_null[0];

    if (mysql_stmt_bind_param(stmt, bind)) {
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
    unsigned long result_length[1] = {0};
    my_bool result_is_null[1] = {0};
    unsigned int result_count[1];

    memset(result_bind, 0, sizeof(result_bind));

    result_bind[0].buffer_type = MYSQL_TYPE_LONG;
    result_bind[0].buffer = (char*)&result_count[0];
    result_bind[0].is_unsigned = true;
    result_bind[0].length = &result_length[0];
    result_bind[0].is_null = &result_is_null[0];

    if (mysql_stmt_bind_result(stmt, result_bind)) {
        fprintf(stderr, "mysql_stmt_bind_result() failed\n");
        mysql_stmt_close(stmt);
        return -1;
    }

    if (mysql_stmt_store_result(stmt)) {
        fprintf(stderr, "mysql_stmt_store_result() failed\n");
        mysql_stmt_close(stmt);
        return -1;
    }

    int rows = 0;
    while (!mysql_stmt_fetch(stmt))
        rows++;

    mysql_stmt_close(stmt);

    return rows > 0 ? 1 : 0;
}

int register_user(MYSQL* conn, const char* username, unsigned long hashed_password) {
    MYSQL_STMT* stmt;
    MYSQL_BIND bind[2];
    memset(bind, 0, sizeof(bind));

    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init() failed\n");
        return -1;
    }

    const char* query = "INSERT INTO users (username, password_hash) VALUES (?, ?)";
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare() failed\n");
        mysql_stmt_close(stmt);
        return -1;
    }

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char*)username;
    bind[0].buffer_length = strlen(username);

    bind[1].buffer_type = MYSQL_TYPE_LONG;
    *(unsigned long*)&bind[1].buffer = hashed_password;

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param() failed\n");
        mysql_stmt_close(stmt);
        return -1;
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute() failed\n");
        mysql_stmt_close(stmt);
        return -1;
    }

    mysql_stmt_close(stmt);
    return 0;
}

int main(int argc, char* argv[]) {
    MYSQL* conn = mysql_init(NULL);

    if (!conn) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    }

    if (mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASS, MYSQL_DB, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    char username[256], password[256], first_name[256], last_name[256], email[256];
    printf("Enter username: ");
    scanf("%255s", username);
    printf("Enter password: ");
    scanf("%255s", password);
    printf("Enter first name: ");
    scanf("%255s", first_name);
    printf("Enter last name: ");
    scanf("%255s", last_name);
    printf("Enter email: ");
    scanf("%255s", email);

    if (check_user_exists(conn, username)) {
        printf("Username already exists.\n");
    } else {
        unsigned long hashed_password = hash_password(password);
        if (register_user(conn, username, hashed_password) == 0) {
            printf("Registration succeeded.\n");
        } else {
            fprintf(stderr, "Failed to register user.\n");
        }
    }

    mysql_close(conn);
    return EXIT_SUCCESS;
}
 

**Note:** Before running the code, ensure you have a MySQL server installed and running with a database named `testdb` and a table `users` defined as follows:


CREATE DATABASE testdb;

USE testdb;

CREATE TABLE users (
    username VARCHAR(255) PRIMARY KEY,
    password_hash UNSIGNED LONG
);


Also, adjust the MYSQL_USER and MYSQL_PASS constants in the code to match your MySQL server's credentials.