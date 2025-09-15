#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "bcrypt.h"

#define SERVER "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "webapp"

void connect_db(MYSQL **conn) {
    *conn = mysql_init(NULL);
    if (!*conn) {
        fprintf(stderr, "%s\n", mysql_error(*conn));
        exit(1);
    }
    if (!mysql_real_connect(*conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(*conn));
        mysql_close(*conn);
        exit(1);
    }
}

void close_db(MYSQL *conn) {
    mysql_close(conn);
}

void register_user(const char *username, const char *password) {
    MYSQL *conn;
    connect_db(&conn);

    unsigned long hashed_password_length = 0;
    unsigned char *hashed_password = bcrypt_hashpw(password, "$2a$", &hashed_password_length);

    if (mysql_query(conn, "INSERT INTO users (username, password) VALUES (?, ?)")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    const char *query = "INSERT INTO users (username, password) VALUES (?, ?)";
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    MYSQL_BIND bind[2];
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;
    bind[0].buffer_length = strlen(username);

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (char *)hashed_password;
    bind[1].buffer_length = hashed_password_length;

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_stmt_close(stmt);

    free(hashed_password);
    close_db(conn);
}

int main() {
    char username[256];
    char password[256];

    printf("Enter username: ");
    scanf("%255s", username);
    printf("Enter password: ");
    scanf("%255s", password);

    register_user(username, password);

    printf("User registered successfully.\n");
    return 0;
}
