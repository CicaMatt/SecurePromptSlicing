#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <mysql/mysql.h>

#define BUFFER_SIZE 256

void hash_password(const char *password, unsigned char *output) {
    EVP_MD_CTX *ctx;
    const EVP_MD *md;

    md = EVP_sha256();
    ctx = EVP_MD_CTX_new();

    if (!EVP_DigestInit_ex(ctx, md, NULL)) {
        exit(EXIT_FAILURE);
    }

    if (!EVP_DigestUpdate(ctx, password, strlen(password))) {
        exit(EXIT_FAILURE);
    }

    if (!EVP_DigestFinal_ex(ctx, output, NULL)) {
        exit(EXIT_FAILURE);
    }

    EVP_MD_CTX_free(ctx);
}

void insert_user(const char *username, const unsigned char *hashed_password) {
    MYSQL *conn;
    MYSQL_STMT *stmt;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "password", "testdb", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }

    stmt = mysql_stmt_init(conn);

    const char *query = "INSERT INTO users (username, password) VALUES (?, ?)";
    if (!mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "Prepare statement failed: %s\n", mysql_stmt_error(stmt));
        exit(EXIT_FAILURE);
    }

    MYSQL_BIND bind[2];
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;

    unsigned char hashed_password_str[BUFFER_SIZE];
    snprintf((char *)hashed_password_str, BUFFER_SIZE, "%02x", *hashed_password);
    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = hashed_password_str;

    if (!mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "Bind parameters failed: %s\n", mysql_stmt_error(stmt));
        exit(EXIT_FAILURE);
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "Execute statement failed: %s\n", mysql_stmt_error(stmt));
        exit(EXIT_FAILURE);
    }

    mysql_stmt_close(stmt);
    mysql_close(conn);
}

int main() {
    char username[BUFFER_SIZE];
    char password[BUFFER_SIZE];

    printf("Enter username: ");
    scanf("%255s", username);

    printf("Enter password: ");
    scanf("%255s", password);

    unsigned char hashed_password[EVP_MAX_MD_SIZE];
    hash_password(password, hashed_password);

    insert_user(username, hashed_password);

    return 0;
}