#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#include <mysql/mysql.h>  // Make sure to install MySQL development libraries

#define USERNAME_SIZE 256
#define PASSWORD_SIZE 256
#define HASHED_PASSWORD_SIZE SHA256_DIGEST_LENGTH * 2 + 1

void hash_password(const char* password, unsigned char hashed_password[HASHED_PASSWORD_SIZE]) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)password, strlen(password), hash);
    
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf((char*)&hashed_password[i * 2], "%02x", hash[i]);
    }
}

void insert_into_database(const char* username, const unsigned char hashed_password[HASHED_PASSWORD_SIZE]) {
    MYSQL* conn;
    MYSQL_RES* res;
    MYSQL_ROW row;

    const char* server = "localhost";
    const char* user = "root";
    const char* password = ""; // Your MySQL root password
    const char* database = "testdb";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO users (username, hashed_password) VALUES ('%s', '%.*s')",
             username, HASHED_PASSWORD_SIZE - 1, hashed_password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_close(conn);
}

int main() {
    char username[USERNAME_SIZE];
    char password[PASSWORD_SIZE];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    unsigned char hashed_password[HASHED_PASSWORD_SIZE];
    hash_password(password, hashed_password);

    insert_into_database(username, hashed_password);

    printf("User inserted successfully.\n");

    return 0;
}


**Note**: Before running this code:
- Ensure you have OpenSSL installed (for SHA256 hashing).
- Install MySQL development libraries and client.
- Configure your MySQL server with the appropriate database (`testdb`) and table (`users`), which should contain columns `username` and `hashed_password`.
- Adjust the MySQL connection parameters as needed.