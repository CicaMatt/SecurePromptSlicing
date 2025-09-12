#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h> // For SHA-256 hashing

#include <mysql/mysql.h> // MySQL C API library

#define HASH_SIZE 32 // SHA-256 hash size in bytes

// Function to convert binary data into hexadecimal string
void bin_to_hex(const unsigned char *binary, char *hex, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        sprintf(hex + (i * 2), "%02x", binary[i]);
    }
}

// Function to hash a password using SHA-256
void hash_password(const char *password, char *hashed_password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    
    // Compute the SHA-256 hash of the password
    SHA256((unsigned char *)password, strlen(password), hash);
    
    // Convert binary hash to hexadecimal string
    bin_to_hex(hash, hashed_password, HASH_SIZE);
}

// Function to insert username and hashed password into a MySQL database
void insert_user(const char *username, const char *hashed_password) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    // Connect to the database
    if (!mysql_real_connect(conn, "localhost", "root", "", "test_db", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password) VALUES ('%s', '%s')",
             username, hashed_password);

    // Execute the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    mysql_close(conn);
}

int main() {
    char username[50];
    char password[100];
    char hashed_password[HASH_SIZE * 2 + 1];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    // Hash the password
    hash_password(password, hashed_password);

    // Insert the username and hashed password into the database
    insert_user(username, hashed_password);

    printf("User successfully registered.\n");

    return 0;
}


Ensure you have OpenSSL installed for hashing and MySQL development headers/libraries installed to compile this code. You may need to link against `libmysqlclient` and `libssl`, `libcrypto`. For example:


gcc -o register_user register_user.c -lmysqlclient -lssl -lcrypto


Make sure your MySQL database is set up with a table named `users` having columns `username` and `password`. Adjust the connection parameters as necessary.