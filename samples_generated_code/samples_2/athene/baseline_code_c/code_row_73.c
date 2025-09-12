#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define MAX_INPUT 100

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "root";
    const char *password = ""; // Set your MySQL password here
    const char *database = "testdb";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char username[MAX_INPUT];
    char input_password[MAX_INPUT];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    char hex_password[2 * SHA256_DIGEST_LENGTH + 1];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", input_password);

    hash_password(input_password, hashed_password);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hex_password + (i * 2), "%02x", hashed_password[i]);
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password) VALUES ('%s', '%s')",
             mysql_real_escape_string(conn, username, strlen(username)),
             mysql_real_escape_string(conn, hex_password, strlen(hex_password)));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("User registered successfully.\n");

    mysql_close(conn);

    return 0;
}