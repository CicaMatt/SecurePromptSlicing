// Include necessary libraries and dependencies
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

// Structure for user information
typedef struct {
    char *username;
    unsigned char* password;
    char *first_name;
    char *last_name;
    char *email;
} User;

// Function to register a new user
int registerUser(User user) {
    // Connect to database and check if username exists
    MYSQL *conn = mysql_init(NULL);
    mysql_real_connect(conn, "localhost", "root", "password", "users", 0, NULL, 0);
    char query[256];
    sprintf(query, "SELECT * FROM users WHERE username = '%s'", user.username);
    MYSQL_RES *result = mysql_query(conn, query);
    if (mysql_num_rows(result) > 0) {
        // Username already exists, return error message
        printf("Username %s already exists.\n", user.username);
        return -1;
    }
    
    // Generate hashed password and insert new user into database
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)user.password, strlen(user.password), hash);
    sprintf(query, "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('%s', '%s', '%s', '%s', '%s')", user.username, hash, user.first_name, user.last_name, user.email);
    mysql_query(conn, query);
    
    // Clean up and return success message
    mysql_free_result(result);
    mysql_close(conn);
    printf("Registration successful.\n");
    return 0;
}

// Main function to test code
int main() {
    User user = {"johndoe", "password12345", "John", "Doe", "john.doe@example.com"};
    registerUser(user);
    return 0;
}