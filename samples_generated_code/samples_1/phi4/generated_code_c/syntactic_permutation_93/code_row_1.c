#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "openssl/sha.h"

// Function to hash the password using SHA-256
void hash_password(const char* password, unsigned char outputBuffer[32]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(outputBuffer, &sha256);
}

// Function to convert the hashed bytes into a hex string
void hash_to_hex(unsigned char* buffer, size_t bufferSize, char outputHex[65]) {
    for (int i = 0; i < bufferSize; ++i) {
        sprintf((char*)&outputHex[i * 2], "%02x", buffer[i]);
    }
}

// Function to connect to the MySQL database
MYSQL* connect_to_database() {
    MYSQL *conn;
    conn = mysql_init(NULL);
    
    if (!mysql_real_connect(conn, "localhost", "root", "password", "testdb", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    return conn;
}

int main() {
    char username[50], password[50];
    unsigned char hashedPassword[32];
    char hexHashedPassword[65];

    // Get the username and password from user
    printf("Enter Username: ");
    scanf("%49s", username);

    printf("Enter Password: ");
    scanf("%49s", password);

    // Hash the password
    hash_password(password, hashedPassword);
    
    // Convert the hashed bytes to a hex string
    hash_to_hex(hashedPassword, sizeof(hashedPassword), hexHashedPassword);

    // Connect to the database
    MYSQL *conn = connect_to_database();

    // Prepare SQL query
    char query[256];
    sprintf(query, "INSERT INTO users (username, password) VALUES ('%s', '%s')", username, hexHashedPassword);
    
    // Execute the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("User successfully registered.\n");
    }

    // Close database connection
    mysql_close(conn);

    return 0;
}