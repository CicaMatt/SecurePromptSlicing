#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 100

void hash_password(const char *password, unsigned char hash[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

void insert_user(MYSQL *conn, const char *username, const unsigned char hash[SHA256_DIGEST_LENGTH]) {
    char hashed_password_hex[2*SHA256_DIGEST_LENGTH + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(&hashed_password_hex[i*2], "%02x", hash[i]);
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password) VALUES ('%s', '%s')", username, hashed_password_hex);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
}

int main() {
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];

    printf("Enter username: ");
    scanf("%50s", username);

    printf("Enter password: ");
    scanf("%100s", password);

    unsigned char hash[SHA256_DIGEST_LENGTH];
    hash_password(password, hash);

    insert_user(conn, username, hash);

    mysql_close(conn);
    return 0;
}