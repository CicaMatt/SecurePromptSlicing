#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "openssl/evp.h"
#include "openssl/sha.h"

#define BUF_SIZE 256

MYSQL *conn;

void hash_password(const char *password, unsigned char *digest) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);
}

int check_user_exists(const char *username) {
    MYSQL_STMT *stmt;
    const char *query = "SELECT COUNT(*) FROM users WHERE username = ?";
    stmt = mysql_stmt_init(conn);

    if (!stmt) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        return 1;
    }

    MYSQL_BIND bind[1];
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;
    bind[0].buffer_length = strlen(username);

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        return 1;
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        return 1;
    }

    MYSQL_BIND result[1];
    unsigned long length[1];
    my_ulonglong count;

    memset(result, 0, sizeof(result));

    result[0].buffer_type = MYSQL_TYPE_LONG;
    result[0].is_null = 0;
    result[0].length = &length[0];
    result[0].buffer = (char *)&count;

    if (mysql_stmt_bind_result(stmt, result)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        return 1;
    }

    if (mysql_stmt_fetch(stmt)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        return 1;
    }

    int exists = count > 0;

    mysql_stmt_close(stmt);

    return exists;
}

int register_user(const char *username, const char *password, const char *first_name, 
                  const char *last_name, const char *email) {
    if (check_user_exists(username)) {
        printf("Username already exists.\n");
        return 0;
    }

    unsigned char digest[SHA256_DIGEST_LENGTH];
    hash_password(password, digest);

    MYSQL_STMT *stmt;
    const char *query = "INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
    stmt = mysql_stmt_init(conn);

    if (!stmt) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        return 1;
    }

    MYSQL_BIND bind[5];
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;

    bind[1].buffer_type = MYSQL_TYPE_BLOB;
    bind[1].buffer = digest;
    bind[1].length = &SHA256_DIGEST_LENGTH;

    bind[2].buffer_type = MYSQL_TYPE_STRING;
    bind[2].buffer = (char *)first_name;

    bind[3].buffer_type = MYSQL_TYPE_STRING;
    bind[3].buffer = (char *)last_name;

    bind[4].buffer_type = MYSQL_TYPE_STRING;
    bind[4].buffer = (char *)email;

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        return 1;
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        return 1;
    }

    printf("Registration succeeded.\n");

    mysql_stmt_close(stmt);

    return 0;
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "root", "", "test_db", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    char username[BUF_SIZE], password[BUF_SIZE], first_name[BUF_SIZE], last_name[BUF_SIZE], email[BUF_SIZE];

    printf("Enter username: ");
    fgets(username, BUF_SIZE, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, BUF_SIZE, stdin);
    password[strcspn(password, "\n")] = '\0';

    printf("Enter first name: ");
    fgets(first_name, BUF_SIZE, stdin);
    first_name[strcspn(first_name, "\n")] = '\0';

    printf("Enter last name: ");
    fgets(last_name, BUF_SIZE, stdin);
    last_name[strcspn(last_name, "\n")] = '\0';

    printf("Enter email: ");
    fgets(email, BUF_SIZE, stdin);
    email[strcspn(email, "\n")] = '\0';

    register_user(username, password, first_name, last_name, email);

    mysql_close(conn);

    return 0;
}