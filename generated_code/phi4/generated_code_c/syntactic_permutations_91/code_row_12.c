#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "sha256.h"

#define DB_SERVER "localhost"
#define DB_USER "root"
#define DB_PASSWORD ""
#define DB_NAME "user_database"

void hash_password(const char *password, unsigned char hashed[32]) {
    sha256((unsigned char *)password, strlen(password), (unsigned char *)hashed);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Initialize MySQL connection
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, DB_SERVER, DB_USER, DB_PASSWORD, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char username[50], password[100];
    unsigned char hashed_password[32];

    printf("Enter Username: ");
    scanf("%49s", username);

    printf("Enter Password: ");
    scanf("%99s", password);

    // Hash the password
    hash_password(password, hashed_password);

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password) VALUES ('%s', '%.*s')",
             username,
             64, hashed_password); // Convert binary data to a hex string

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("User added successfully.\n");

    mysql_close(conn);

    return 0;
}

// Dummy SHA256 implementation
void sha256(const unsigned char *input, size_t len, unsigned char output[32]) {
    for (int i = 0; i < 32; ++i) {
        output[i] = i; // Replace with actual hashing logic
    }
}


**Note**: This code includes a dummy `sha256` function. For real-world use, you should replace this with an actual SHA-256 implementation, such as the one from OpenSSL or another cryptographic library. Also, ensure your database and table (`users`) are properly set up to store usernames and hashed passwords in hexadecimal format.