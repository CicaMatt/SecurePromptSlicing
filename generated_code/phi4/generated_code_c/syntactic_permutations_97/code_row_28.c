#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HASH_SIZE 64

void hash_password(const char *password, char *hashed) {
    unsigned long l = strlen(password);
    for (unsigned long i = 0; i < l; ++i)
        sprintf(hashed + (i << 1), "%02x", password[i]);
    hashed[l << 1] = '\0';
}

int check_username_exists(MYSQL *conn, const char *username) {
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[1];
    my_bool is_null[1] = { 0 };
    unsigned long length[1] = { 0 };

    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init() failed\n");
        return -1;
    }

    const char *query = "SELECT username FROM users WHERE username=?";
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare() failed\n");
        mysql_stmt_close(stmt);
        return -1;
    }

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;
    bind[0].is_null = &is_null[0];
    bind[0].length = &length[0];

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

    MYSQL_RES *result = mysql_stmt_result_metadata(stmt);
    if (!result) {
        int affected_rows = mysql_stmt_affected_rows(stmt);
        if (affected_rows > 0)
            printf("Username already exists.\n");
        else
            printf("Registration succeeded.\n");

        mysql_free_result(result);
        mysql_stmt_close(stmt);
        return affected_rows > 0 ? 1 : 0;
    }

    mysql_free_result(result);
    mysql_stmt_close(stmt);
    return 0;
}

int register_user(MYSQL *conn, const char *username, const char *password, 
                  const char *first_name, const char *last_name, const char *email) {
    if (check_username_exists(conn, username)) {
        return -1;
    }

    MYSQL_STMT *stmt;
    MYSQL_BIND bind[5];
    my_bool is_null[5] = { 0 };
    unsigned long length[5] = { 0 };

    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init() failed\n");
        return -1;
    }

    const char *query = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare() failed\n");
        mysql_stmt_close(stmt);
        return -1;
    }

    char hashed_password[HASH_SIZE];
    hash_password(password, hashed_password);

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (char *)hashed_password;

    bind[2].buffer_type = MYSQL_TYPE_STRING;
    bind[2].buffer = (char *)first_name;

    bind[3].buffer_type = MYSQL_TYPE_STRING;
    bind[3].buffer = (char *)last_name;

    bind[4].buffer_type = MYSQL_TYPE_STRING;
    bind[4].buffer = (char *)email;

    for (int i = 0; i < 5; ++i) {
        bind[i].is_null = &is_null[i];
        bind[i].length = &length[i];
    }

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

    printf("Registration succeeded.\n");

    mysql_stmt_close(stmt);
    return 0;
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    }

    if (mysql_real_connect(conn, "localhost", "root", "password", "database_name", 3306, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    char username[50], password[50], first_name[50], last_name[50], email[100];
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);
    printf("Enter first name: ");
    scanf("%49s", first_name);
    printf("Enter last name: ");
    scanf("%49s", last_name);
    printf("Enter email: ");
    scanf("%99s", email);

    if (register_user(conn, username, password, first_name, last_name, email) == -1) {
        fprintf(stderr, "Registration failed.\n");
    }

    mysql_close(conn);
    return EXIT_SUCCESS;
}