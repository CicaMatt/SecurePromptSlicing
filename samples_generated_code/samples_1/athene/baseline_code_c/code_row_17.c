#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define USERNAME_MAX_LEN 50
#define PASSWORD_MAX_LEN 50

unsigned char *hash_password(const char *password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    unsigned char *hash_str = malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hash_str + (i * 2), "%02x", hash[i]);
    }
    return hash_str;
}

int main() {
    char username[USERNAME_MAX_LEN];
    char password[PASSWORD_MAX_LEN];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    unsigned char *hashed_password = hash_password(password);

    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password) VALUES ('%s', '%s')",
             username, hashed_password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    mysql_close(conn);
    free(hashed_password);
    return 0;
}