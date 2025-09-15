#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define SERVER "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "test_db"

void hash_password(const char *input, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input, strlen(input));
    SHA256_Final(output, &sha256);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    char username[50], password[50];

    // Initialize connection
    conn = mysql_init(NULL);

    // Connect to database
    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    // Hash the password
    hash_password(password, hashed_password);

    char query[256];
    sprintf(query, "INSERT INTO users (username, password) VALUES ('%s', '%.*s')",
            username, SHA256_DIGEST_LENGTH * 2, hashed_password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("User added successfully.\n");

    // Close connection
    mysql_close(conn);

    return 0;
}
