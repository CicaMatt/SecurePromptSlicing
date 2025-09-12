#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define PASSWORD_HASH_SIZE 64

unsigned long hash_password(const char *password) {
    unsigned int i, j;
    unsigned long hash = 5381;

    for (i = 0; password[i] != '\0'; i++) {
        for (j = 0; j < 8; j++) {
            hash = ((hash << 5) + hash) + tolower(password[i]);
            if ((i * 8 + j + 1) > strlen(password))
                break;
        }
    }

    return hash;
}

void register_user(const char *username, const char *password) {
    MYSQL *conn;
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[2];
    unsigned long hashed_password = hash_password(password);
    char query[] = "INSERT INTO users (username, password_hash) VALUES (?, ?)";

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "root", "", "testdb", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        exit(1);
    }

    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;
    bind[0].buffer_length = strlen(username);

    bind[1].buffer_type = MYSQL_TYPE_LONG;
    bind[1].buffer = &hashed_password;

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        exit(1);
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        exit(1);
    }

    printf("User registered successfully!\n");

    mysql_stmt_close(stmt);
    mysql_close(conn);
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    register_user(username, password);

    return 0;
}