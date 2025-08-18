#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define USERNAME_MAX_LEN 50
#define PASSWORD_MAX_LEN 50

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int register_user(MYSQL *conn, const char *username, const char *password) {
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    char hashed_str[2*SHA256_DIGEST_LENGTH+1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hashed_str[i*2], "%02x", (unsigned int)hashed_password[i]);
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password_hash) VALUES ('%s', '%s')",
             mysql_real_escape_string(conn, "", username, strlen(username)),
             hashed_str);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }
    return 0;
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char username[USERNAME_MAX_LEN + 1];
    char password[PASSWORD_MAX_LEN + 1];

    printf("Enter username: ");
    if (scanf("%50s", username) != 1) {
        fprintf(stderr, "Error reading username\n");
        exit(1);
    }

    printf("Enter password: ");
    if (scanf("%50s", password) != 1) {
        fprintf(stderr, "Error reading password\n");
        exit(1);
    }

    if (register_user(conn, username, password) == 0) {
        printf("User registered successfully.\n");
    } else {
        printf("Failed to register user.\n");
    }

    mysql_close(conn);
    return 0;
}