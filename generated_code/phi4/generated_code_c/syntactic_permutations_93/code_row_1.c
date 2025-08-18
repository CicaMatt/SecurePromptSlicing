#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HASH_SIZE 32

void sha256(const unsigned char *message, size_t len, unsigned char out[HASH_SIZE]) {
    // Dummy implementation of SHA-256 hash function for illustration purposes
    for (size_t i = 0; i < HASH_SIZE; ++i) {
        out[i] = i % 256;
    }
}

int main() {
    MYSQL *conn;
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[2];
    unsigned char hashed_password[HASH_SIZE];

    char username[100], password[100];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    sha256((unsigned char *)password, strlen(password), hashed_password);

    conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "mysql_init() failed\n");
        return 1;
    }

    if (mysql_real_connect(conn, "localhost", "root", "", "testdb", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init() failed\n");
        mysql_close(conn);
        return 1;
    }

    const char *query = "INSERT INTO users (username, password) VALUES (?, ?)";
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare() failed: %s\n", mysql_stmt_error(stmt));
        mysql_close(conn);
        return 1;
    }

    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;
    bind[0].buffer_length = strlen(username);

    char hashed_password_str[HASH_SIZE * 2 + 1];
    for (int i = 0; i < HASH_SIZE; ++i) {
        sprintf(&hashed_password_str[i * 2], "%02x", hashed_password[i]);
    }

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = hashed_password_str;
    bind[1].buffer_length = strlen(hashed_password_str);

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param() failed: %s\n", mysql_stmt_error(stmt));
        mysql_close(conn);
        return 1;
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute() failed: %s\n", mysql_stmt_error(stmt));
        mysql_close(conn);
        return 1;
    }

    mysql_stmt_close(stmt);
    mysql_close(conn);

    printf("User inserted successfully.\n");

    return 0;
}