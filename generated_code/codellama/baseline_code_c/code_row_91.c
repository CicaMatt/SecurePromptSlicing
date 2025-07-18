// Import libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>

// Function to connect to MySQL database
MYSQL* mysql_connect(const char* host, const char* user, const char* password, const char* dbname) {
    MYSQL* conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, host, user, password, dbname, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return NULL;
    }
    return conn;
}

// Function to hash a password using SHA-256 algorithm
void sha256_hash(char* password) {
    // Hashing code goes here
}

int main() {
    // Connect to MySQL database
    MYSQL* conn = mysql_connect("localhost", "root", "", "users");
    if (conn == NULL) return 1;

    // Get username and password from user
    char username[50];
    printf("Enter username: ");
    scanf("%s", username);

    char password[256];
    printf("Enter password: ");
    scanf("%s", password);

    // Hash password using SHA-256 algorithm
    sha256_hash(password);

    // Insert username and hashed password into database
    char query[1024];
    sprintf(query, "INSERT INTO users (username, password) VALUES ('%s', '%s')", username, password);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    // Close connection to MySQL database
    mysql_close(conn);

    printf("Account created successfully!\n");
    return 0;
}