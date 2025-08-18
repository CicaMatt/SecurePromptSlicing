#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define PASSWORD_HASH_LEN 41

void hash_password(const char *password, char *hashed_password) {
    unsigned long hash = 5381;
    int c;

    while ((c = *password++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    sprintf(hashed_password, "%lu", hash);
}

int check_username_exists(MYSQL *conn, const char *username) {
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[1];
    my_bool is_null = 0;
    unsigned long length = 0;

    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init() failed\n");
        return -1;
    }

    const char *query = "SELECT COUNT(*) FROM users WHERE username = ?";
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare() failed\n");
        mysql_stmt_close(stmt);
        return -1;
    }

    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;
    bind[0].buffer_length = strlen(username);

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

    int count = 0;
    unsigned long count_length = 0;

    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_LONG;
    bind[0].is_null = &is_null;
    bind[0].length = &count_length;
    bind[0].buffer = (char *)&count;

    if (mysql_stmt_bind_result(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_result() failed\n");
        mysql_stmt_close(stmt);
        return -1;
    }

    if (mysql_stmt_store_result(stmt)) {
        fprintf(stderr, "mysql_stmt_store_result() failed\n");
        mysql_stmt_close(stmt);
        return -1;
    }

    if (mysql_stmt_fetch(stmt) == 0 && !is_null[0]) {
        mysql_stmt_close(stmt);
        return count > 0 ? 1 : 0;
    } else {
        fprintf(stderr, "mysql_stmt_fetch() failed\n");
        mysql_stmt_close(stmt);
        return -1;
    }
}

int insert_user(MYSQL *conn, const char *username, const char *hashed_password) {
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[2];
    my_bool is_null = 0;

    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init() failed\n");
        return -1;
    }

    const char *query = "INSERT INTO users (username, password) VALUES (?, ?)";
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare() failed\n");
        mysql_stmt_close(stmt);
        return -1;
    }

    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;
    bind[0].buffer_length = strlen(username);

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (char *)hashed_password;
    bind[1].buffer_length = PASSWORD_HASH_LEN - 1;

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

int main() {
    MYSQL *conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char username[100], first_name[50], last_name[50], email[100], password[100];
    printf("Enter first name: ");
    scanf("%49s", first_name);
    printf("Enter last name: ");
    scanf("%49s", last_name);
    printf("Enter email: ");
    scanf("%99s", email);
    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    char hashed_password[PASSWORD_HASH_LEN];
    hash_password(password, hashed_password);

    if (check_username_exists(conn, username)) {
        printf("Username already exists.\n");
    } else {
        if (insert_user(conn, username, hashed_password) == 0) {
            printf("Registration succeeded.\n");
        } else {
            fprintf(stderr, "Failed to insert user into database.\n");
        }
    }

    mysql_close(conn);
    return 0;
}