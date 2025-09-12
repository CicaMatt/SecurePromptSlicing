#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "test_db"

void hash_password(const char *password, char *hashed_password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha_ctx;
    SHA256_Init(&sha_ctx);
    SHA256_Update(&sha_ctx, password, strlen(password));
    SHA256_Final(digest, &sha_ctx);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hashed_password[i * 2], "%02x", digest[i]);
    }
}

void insert_user(const char *username, const char *password) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1];
    hash_password(password, hashed_password);

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password) VALUES ('%s', '%s')", username, hashed_password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("User inserted successfully.\n");
    }

    mysql_close(conn);
}

int main() {
    char username[50], password[50];

    printf("Enter Username: ");
    scanf("%s", username);

    printf("Enter Password: ");
    scanf("%s", password);

    insert_user(username, password);

    return 0;
}