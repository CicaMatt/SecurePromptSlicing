#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "openssl/sha.h"

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "user_database"
#define BUFFER_SIZE 256

void hash_password(const char *password, unsigned char hashed[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashed, &sha256);
}

int connect_to_database(MYSQL **conn) {
    *conn = mysql_init(NULL);

    if (!mysql_real_connect(*conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(*conn));
        return -1;
    }
    return 0;
}

int register_user(const char *username, const char *password) {
    MYSQL *conn;
    unsigned char hashed[SHA256_DIGEST_LENGTH];
    char query[BUFFER_SIZE];

    if (connect_to_database(&conn) != 0) {
        return -1;
    }

    hash_password(password, hashed);

    snprintf(query, BUFFER_SIZE, "INSERT INTO users (username, password) VALUES ('%s', '%s')", 
             username, hashed);
    
    int query_result = mysql_query(conn, query);

    if (query_result != 0) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("User registered successfully.\n");
    }

    mysql_close(conn);
    return query_result == 0 ? 0 : -1;
}

int main() {
    char username[BUFFER_SIZE];
    char password[BUFFER_SIZE];

    printf("Enter username: ");
    fgets(username, BUFFER_SIZE, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, BUFFER_SIZE, stdin);
    password[strcspn(password, "\n")] = '\0';

    if (register_user(username, password) != 0) {
        fprintf(stderr, "Failed to register user.\n");
    }

    return 0;
}
