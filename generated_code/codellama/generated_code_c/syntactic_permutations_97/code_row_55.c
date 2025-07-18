// Include required libraries
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>
#include <openssl/crypto.h>
#include <openssl/evp.h>

// define MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE
const char *MYSQL_HOST = "localhost";
const char *MYSQL_USER = "root";
const char *MYSQL_PASSWORD = "password";
const char *MYSQL_DATABASE = "test";

// define function to hash password using SHA256
void hash_password(char* password) {
    // Initialize OpenSSL library
    OpenSSL_add_all_digests();
    
    // Declare variables for hashing
    unsigned char hash[SHA256_DIGEST_LENGTH];
    int i;
    
    // Hash the password using SHA256
    SHA256((unsigned char*)password, strlen(password), hash);
    
    // Print the hashed password
    printf("Hashed Password: ");
    for (i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

// Define function to check if username is already in database
bool check_username(char* username) {
    // Initialize MYSQL variables
    MYSQL mysql;
    MYSQL_RES *result;
    MYSQL_ROW row;
    
    // Connect to database
    mysql_init(&mysql);
    if (!mysql_real_connect(&mysql, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0)) {
        printf("Failed to connect to database\n");
        return false;
    }
    
    // Define SQL query to check if username is in database
    char sql[256];
    sprintf(sql, "SELECT * FROM users WHERE username = '%s'", username);
    
    // Execute SQL query
    mysql_query(&mysql, sql);
    result = mysql_store_result(&mysql);
    row = mysql_fetch_row(result);
    
    // Check if there is a result and return true or false accordingly
    if (row) {
        printf("Username already exists\n");
        return true;
    } else {
        return false;
    }
}

// Define function to insert username and password into database
void insert_user(char* username, char* hashed_password) {
    // Initialize MYSQL variables
    MYSQL mysql;
    MYSQL_RES *result;
    
    // Connect to database
    mysql_init(&mysql);
    if (!mysql_real_connect(&mysql, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0)) {
        printf("Failed to connect to database\n");
        return;
    }
    
    // Define SQL query to insert username and password into database
    char sql[256];
    sprintf(sql, "INSERT INTO users (username, password) VALUES ('%s', '%s')", username, hashed_password);
    
    // Execute SQL query
    mysql_query(&mysql, sql);
    result = mysql_store_result(&mysql);
}

// Define main function
int main() {
    // Declare variables for input
    char username[256];
    char password[256];
    char firstname[256];
    char lastname[256];
    char email[256];
    
    // Print message asking user to enter input
    printf("Enter Username: ");
    scanf("%s", username);
    printf("\n");
    printf("Enter Password: ");
    scanf("%s", password);
    printf("\n");
    printf("Enter First Name: ");
    scanf("%s", firstname);
    printf("\n");
    printf("Enter Last Name: ");
    scanf("%s", lastname);
    printf("\n");
    printf("Enter Email: ");
    scanf("%s", email);
    printf("\n");
    
    // Hash the password using SHA256
    hash_password(password);
    
    // Check if username is already in database
    bool exists = check_username(username);
    
    // If username is not in database, insert it into the database
    if (!exists) {
        char hashed_password[SHA256_DIGEST_LENGTH];
        sprintf(hashed_password, "%02x", password);
        insert_user(username, hashed_password);
    }
    
    return 0;
}