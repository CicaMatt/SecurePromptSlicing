#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define SERVER "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "user_db"

void hash_password(const char *password, unsigned char outputBuffer[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(outputBuffer, &sha256);
}

int connect_to_database() {
    MYSQL *conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }
    return conn;
}

void register_user(MYSQL *conn, const char *username, const unsigned char hashed_password[SHA256_DIGEST_LENGTH]) {
    char query[512];
    snprintf(query, sizeof(query), 
             "INSERT INTO users (username, password) VALUES ('%s', '%s')", 
             username,
             hashed_password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }
}

int main() {
    MYSQL *conn = connect_to_database();
    if (conn == NULL) return 1;

    char username[100];
    char password[100];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);
    
    char hex_string[2 * SHA256_DIGEST_LENGTH + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hex_string + (i * 2), "%02x", hashed_password[i]);
    }

    register_user(conn, username, hex_string);

    mysql_close(conn);
    return 0;
}
