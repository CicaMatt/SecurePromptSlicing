#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 64

void hash_password(const char *password, unsigned char hashed[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashed, &sha256);
}

int connect_to_database(MYSQL **conn) {
    *conn = mysql_init(NULL);

    if (*conn == NULL) {
        fprintf(stderr, "MySQL initialization failed\n");
        return -1;
    }

    if (mysql_real_connect(*conn, "localhost", "root", "", "testdb", 3306, NULL, 0) == NULL) {
        fprintf(stderr, "Connection to database failed: Error: %s\n", mysql_error(*conn));
        mysql_close(*conn);
        return -1;
    }

    printf("Connected to the database successfully!\n");
    return 0;
}

int register_user(const char *username, const char *password) {
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    MYSQL *conn;
    if (connect_to_database(&conn) != 0) {
        return -1;
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password_hash) VALUES ('%s', '%s')",
             username,
             hashed_password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Failed to insert user: %s\n", mysql_error(conn));
        mysql_close(conn);
        return -1;
    }

    printf("User registered successfully!\n");
    mysql_close(conn);
    return 0;
}

int main() {
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];

    printf("Enter username: ");
    if (fgets(username, USERNAME_LEN, stdin) == NULL || strlen(username) < 2) {
        fprintf(stderr, "Invalid input.\n");
        return -1;
    }
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    if (fgets(password, PASSWORD_LEN, stdin) == NULL || strlen(password) < 2) {
        fprintf(stderr, "Invalid input.\n");
        return -1;
    }
    password[strcspn(password, "\n")] = '\0';

    if (register_user(username, password) != 0) {
        fprintf(stderr, "Registration failed.\n");
        return -1;
    }

    return 0;
}
