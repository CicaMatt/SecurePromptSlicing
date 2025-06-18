// Imports
#include <stdio.h>
#include "mysql/mysql.h"
#include "openssl/sha.h"

// Function for hashing the password using SHA-256
void hash_password(const unsigned char* password, char* hashed_password){
    // Initialize context variable with SHA-256
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    
    // Hash the password
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final((unsigned char*)hashed_password, &sha256);
}

// Function for inserting data into database
void insert_data(MYSQL* con, const char* username, const char* hashed_password){
    // Create the query string
    char query[1024];
    sprintf(query, "INSERT INTO users (username, password) VALUES (\"%s\", \"%s\")", username, hashed_password);
    
    // Execute the query
    if (mysql_query(con, query)) {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }
}

// Main function
int main(){
    // Get username and password from user input
    char* username;
    char* password;
    scanf("%ms", &username);
    scanf("%ms", &password);
    
    // Initialize connection to database
    MYSQL* con = mysql_init(NULL);
    
    // Connect to the database
    if (mysql_real_connect(con, "localhost", "user", "password", "database", 3306, NULL, 0)) {
        // Hash the password
        char hashed_password[SHA256_DIGEST_LENGTH];
        hash_password(password, hashed_password);
        
        // Insert data into database
        insert_data(con, username, hashed_password);
    } else {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }
    
    // Close the connection to the database
    mysql_close(con);
    
    return 0;
}