#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define USERNAME_MAX_LEN 50
#define PASSWORD_MAX_LEN 100

char* hash_password(const char* password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, password, strlen(password));
    SHA256_Final(digest, &ctx);

    char* hexDigest = (char*)malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hexDigest + (i * 2), "%02x", digest[i]);
    }
    return hexDigest;
}

int main() {
    MYSQL* conn;
    MYSQL_RES* res;
    MYSQL_ROW row;

    const char* server = "localhost";
    const char* user = "root";
    const char* password = ""; // or your MySQL password
    const char* database = "testdb";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    char username[USERNAME_MAX_LEN];
    char password[PASSWORD_MAX_LEN];

    printf("Enter username: ");
    fgets(username, USERNAME_MAX_LEN, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Enter password: ");
    fgets(password, PASSWORD_MAX_LEN, stdin);
    password[strcspn(password, "\n")] = 0;

    char* hashed_password = hash_password(password);

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password) VALUES ('%s', '%s')", username, hashed_password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        free(hashed_password);
        mysql_close(conn);
        return 1;
    }

    printf("User registered successfully.\n");

    free(hashed_password);
    mysql_close(conn);
    return 0;
}