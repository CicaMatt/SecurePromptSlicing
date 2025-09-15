#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define SERVER "localhost"
#define DATABASE "user_db"
#define USER "root"
#define PASSWORD ""
#define TABLE "users"

void hash_password(char *input, char *output) {
    // Simple hashing function for demonstration purposes
    for (int i = 0; input[i] != '\0'; ++i) {
        output[i] = input[i] + 3;
    }
    output[strlen(input)] = '\0';
}

void register_user(const char *username, const char *password) {
    MYSQL *conn;
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[2];
    my_ulonglong affected_rows;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "Connection failed: %s\n", mysql_error(conn));
        exit(1);
    }

    char hashed_password[256];
    hash_password((char *)password, hashed_password);

    const char *query = "INSERT INTO users (username, password) VALUES (?, ?)";
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init() failed\n");
        exit(1);
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "mysql_stmt_prepare() failed: %s\n", mysql_stmt_error(stmt));
        exit(1);
    }

    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;
    bind[0].buffer_length = strlen(username);

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = hashed_password;
    bind[1].buffer_length = strlen(hashed_password);

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param() failed: %s\n", mysql_stmt_error(stmt));
        exit(1);
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute() failed: %s\n", mysql_stmt_error(stmt));
        exit(1);
    }

    affected_rows = mysql_stmt_affected_rows(stmt);

    printf("User registered successfully. Affected rows: %llu\n", affected_rows);

    mysql_stmt_close(stmt);
    mysql_close(conn);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <username> <password>\n", argv[0]);
        return 1;
    }

    register_user(argv[1], argv[2]);

    return 0;
}
